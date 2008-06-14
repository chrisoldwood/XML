////////////////////////////////////////////////////////////////////////////////
//! \file   Reader.cpp
//! \brief  The Reader class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Reader.hpp"
#include "IOException.hpp"
#include "CharTable.hpp"
#include "TextNode.hpp"
#include "ElementNode.hpp"
#include "CommentNode.hpp"
#include "ProcessingNode.hpp"
#include "DocTypeNode.hpp"
#include "CDataNode.hpp"

namespace XML
{

//! The stream character lookup table.
static CharTable s_oCharTable;

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Reader::Reader()
	: m_nFlags(DEFAULT)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Reader::~Reader()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Helper function for appending a child node.

template<typename T>
inline void AppendChild(NodePtr pNode, Core::RefCntPtr<T>& pChild)
{
	ASSERT((pNode->Type() == DOCUMENT_NODE) || (pNode->Type() == ELEMENT_NODE));

	if (pNode->Type() == DOCUMENT_NODE)
		Core::static_ptr_cast<Document>(pNode)->AppendChild(pChild);
	else
		Core::static_ptr_cast<ElementNode>(pNode)->AppendChild(pChild);
}

////////////////////////////////////////////////////////////////////////////////
//! Read a document from a pair of raw string pointers.

DocumentPtr Reader::ReadDocument(const tchar* pcBegin, const tchar* pcEnd, uint nFlags)
{
	Initialise(pcBegin, pcEnd, nFlags);

	DocumentPtr pDoc(new Document);

	// Start by appending to the document node.
	m_oNodeStack.push(pDoc);

	// For all nodes...
	while (m_pcCurrent != m_pcEnd)
	{
		const tchar* pcNodeBegin = m_pcCurrent;

		// Is a tag?
		if (*m_pcCurrent == TXT('<'))
		{
			++m_pcCurrent;

			// A comment or document type tag?
			if (*m_pcCurrent == TXT('!'))
			{
				if (m_pcCurrent != m_pcEnd)
				{
					++m_pcCurrent;

					if (*m_pcCurrent == TXT('-'))
					{
						ReadCommentTag(pcNodeBegin);
					}
					else if (*m_pcCurrent == TXT('D'))
					{
						ReadDocTypeTag(pcNodeBegin);
					}
					else if (*m_pcCurrent == TXT('['))
					{
						ReadCDataSection(pcNodeBegin);
					}
					else
					{
						throw IOException(TXT("Invalid node type"));
					}
				}
				else
				{
					throw IOException(TXT("EOF encountered reading a node"));
				}
			}
			// A processing instruction tag?
			else if (*m_pcCurrent == TXT('?'))
			{
				ReadProcessingTag(pcNodeBegin);
			}
			// An element tag.
			else
			{
				ReadElementTag(pcNodeBegin);
			}
		}
		// Is text.
		else
		{
			ReadTextNode(pcNodeBegin);
		}
	}

	// Missing one or more end tags?
	if (m_oNodeStack.size() > 1)
		throw IOException(TXT("One or more end tags were missing"));

	// Document empty?
	if (!pDoc->HasRootElement())
		throw IOException(TXT("The XML document was empty"));

	return pDoc;
}

////////////////////////////////////////////////////////////////////////////////
//! Initialise the internal state ready for reading.

void Reader::Initialise(const tchar* pcBegin, const tchar* pcEnd, uint nFlags)
{
	m_pcBegin   = pcBegin;
	m_pcEnd     = pcEnd;
	m_pcCurrent = pcBegin;
	m_nFlags    = nFlags;

	while (!m_oNodeStack.empty())
		m_oNodeStack.pop();
}

////////////////////////////////////////////////////////////////////////////////
//! Read and parse a comment tag.

void Reader::ReadCommentTag(const tchar* pcNodeBegin)
{
	ASSERT((m_pcCurrent-pcNodeBegin) >= 2);

	// Find node terminator.
	while ( (m_pcCurrent != m_pcEnd) && ((*m_pcCurrent != TXT('>') || (tstrncmp(m_pcCurrent-2, TXT("-->"), 3) != 0))) )
		++m_pcCurrent;

	if (m_pcCurrent == m_pcEnd)
		throw IOException(TXT("EOF encountered reading a comment node"));

	ASSERT(*m_pcCurrent == TXT('>'));
	++m_pcCurrent;

	const tchar* pcNodeEnd = m_pcCurrent;
	size_t       nLength   = pcNodeEnd - pcNodeBegin;

	// Must be at least "<!---->"
	if ( (nLength < 7)
	  || (tstrncmp(pcNodeBegin, TXT("<!--"), 4) != 0)
	  || (tstrncmp(pcNodeEnd-3, TXT("-->"),  3) != 0) )
	{
		throw IOException(TXT("Invalid comment node format"));
	}

	// Keeping comments?
	if ((m_nFlags & DISCARD_COMMENTS) == 0)
	{
		// Adjust iterators for the inner text.
		pcNodeBegin += 4;
		pcNodeEnd   -= 3;

		// Create node and append to collection.
		CommentNodePtr pNode = CommentNodePtr(new CommentNode(tstring(pcNodeBegin, pcNodeEnd)));
		
		AppendChild(m_oNodeStack.top(), pNode);
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read and parse a processing instruction tag.

void Reader::ReadProcessingTag(const tchar* pcNodeBegin)
{
	// Find node terminator.
	while ( (m_pcCurrent != m_pcEnd) && (*m_pcCurrent != TXT('>')) )
		++m_pcCurrent;

	if (m_pcCurrent == m_pcEnd)
		throw IOException(TXT("EOF encountered reading a processing instruction node"));

	ASSERT(*m_pcCurrent == TXT('>'));
	++m_pcCurrent;

	const tchar* pcNodeEnd = m_pcCurrent;
	size_t       nLength   = pcNodeEnd - pcNodeBegin;

	// Must be at least "<?_?>"
	if ( (nLength < 5)
	  || (tstrncmp(pcNodeBegin, TXT("<?"), 2) != 0)
	  || (tstrncmp(pcNodeEnd-2, TXT("?>"), 2) != 0) )
	{
		throw IOException(TXT("Invalid processing instruction node format"));
	}

	// Keeping processing instructions?
	if ((m_nFlags & DISCARD_PROC_INSTNS) == 0)
	{
		// Adjust iterators for the inner text.
		pcNodeBegin += 2;
		pcNodeEnd   -= 2;

		tstring    strTarget;
		Attributes vAttribs;

		// Read the target.
		const tchar* pcCurrent = ReadIdentifier(pcNodeBegin, pcNodeEnd, strTarget);	

		while (pcCurrent != pcNodeEnd)
		{
			// Skip whitespace.
			while ( (pcCurrent != pcNodeEnd) && (s_oCharTable.IsWhitespace(*pcCurrent)) )
				++pcCurrent;

			// Read attribute, if present.
			if (pcCurrent != pcNodeEnd)
			{
				tstring strName, strValue;

				pcCurrent = ReadAttribute(pcCurrent, pcNodeEnd, strName, strValue);

				vAttribs.SetAttribute(AttributePtr(new Attribute(strName, strValue)));
			}
		}

		// Create node and append to collection.
		ProcessingNodePtr pNode = ProcessingNodePtr(new ProcessingNode(strTarget, vAttribs));
		
		AppendChild(m_oNodeStack.top(), pNode);
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read and create a text node.

void Reader::ReadTextNode(const tchar* pcNodeBegin)
{
	bool bWhitespaceOnly = true;

	// Read up to a tag marker.
	while ( (m_pcCurrent != m_pcEnd) && (*m_pcCurrent != TXT('<')) )
	{
		if (!tisspace(static_cast<utchar>(*m_pcCurrent)))
			bWhitespaceOnly = false;

		++m_pcCurrent;
	}

	const tchar* pcNodeEnd = m_pcCurrent;

	// Append text node, if present.
	if (pcNodeBegin != pcNodeEnd)
	{
		// Disallow text outside the root element.
		if ( (!bWhitespaceOnly) && (m_oNodeStack.size() == 1) )
			throw IOException(TXT("Non-whitespace character(s) outside the root element"));

		// Not just whitespace OR we're keeping whitespace?
		if (!bWhitespaceOnly || ((m_nFlags & DISCARD_WHITESPACE) == 0))
		{
			// Create node and append to collection.
			TextNodePtr pNode = TextNodePtr(new TextNode(tstring(pcNodeBegin, pcNodeEnd)));

			AppendChild(m_oNodeStack.top(), pNode);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read and parse an element tag. If the tag is a start tag or empty tag an
//! element node is returned. If it's a close tag, no node is returned.

void Reader::ReadElementTag(const tchar* pcNodeBegin)
{
	// Find node terminator.
	while ( (m_pcCurrent != m_pcEnd) && (*m_pcCurrent != TXT('>')) )
	{
		// Apostrophe enclosed string?
		if (*m_pcCurrent == TXT('\''))
		{
			++m_pcCurrent;

			while ( (m_pcCurrent != m_pcEnd) && (*m_pcCurrent != TXT('\'')) )
				++m_pcCurrent;

			if (*m_pcCurrent == TXT('\''))
				++m_pcCurrent;
		}
		// Double-quote enclosed string?
		else if (*m_pcCurrent == TXT('\"'))
		{
			++m_pcCurrent;

			while ( (m_pcCurrent != m_pcEnd) && (*m_pcCurrent != TXT('\"')) )
				++m_pcCurrent;

			if (*m_pcCurrent == TXT('\"'))
				++m_pcCurrent;
		}
		else
		{
			++m_pcCurrent;
		}
	}

	if (m_pcCurrent == m_pcEnd)
		throw IOException(TXT("EOF encountered reading an element node"));

	ASSERT(*m_pcCurrent == TXT('>'));
	++m_pcCurrent;

	const tchar* pcNodeEnd = m_pcCurrent;
	size_t       nLength   = pcNodeEnd - pcNodeBegin;

	// Must be at least "<X>"
	if (nLength < 3)
		throw IOException(TXT("Invalid element node format"));

	// Is the end of an element?
	if (*(pcNodeBegin+1) == TXT('/'))
	{
		// Adjust iterators for the inner text.
		pcNodeBegin += 2;
		pcNodeEnd   -= 1;

		tstring strName(pcNodeBegin, pcNodeEnd);

		ASSERT(!m_oNodeStack.empty());

		// Validate tag matches the last open one.
		NodePtr pNode = m_oNodeStack.top();

		if (pNode->Type() != ELEMENT_NODE)
			throw IOException(TXT("End tag encountered without a matching start tag"));

		ElementNodePtr pElement = Core::static_ptr_cast<ElementNode>(pNode);

		if (pElement->Name() != strName)
			throw IOException(TXT("End tag does not match the last start tag"));

		// Valid.
		m_oNodeStack.pop();
	}
	// Is an open or empty element.
	else
	{
		// Adjust iterators for the inner text.
		pcNodeBegin += 1;

		if (*(pcNodeEnd-2) == TXT('/'))
			pcNodeEnd -= 2;
		else
			pcNodeEnd -= 1;

		tstring    strName;
		Attributes vAttribs;

		// Read the target.
		const tchar* pcCurrent = ReadIdentifier(pcNodeBegin, pcNodeEnd, strName);	

		while (pcCurrent != pcNodeEnd)
		{
			// Skip whitespace.
			while ( (pcCurrent != pcNodeEnd) && (s_oCharTable.IsWhitespace(*pcCurrent)) )
				++pcCurrent;

			// Read attribute, if present.
			if (pcCurrent != pcNodeEnd)
			{
				tstring strName, strValue;

				pcCurrent = ReadAttribute(pcCurrent, pcNodeEnd, strName, strValue);

				vAttribs.SetAttribute(AttributePtr(new Attribute(strName, strValue)));
			}
		}

		// Create node and append to collection.
		ElementNodePtr pNode(new ElementNode(strName, vAttribs));

		AppendChild(m_oNodeStack.top(), pNode);

		// Track start tags.
		if (*pcNodeEnd != TXT('/'))
			m_oNodeStack.push(pNode);
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read and parse a document type tag.

void Reader::ReadDocTypeTag(const tchar* pcNodeBegin)
{
	// Find node terminator.
	while ( (m_pcCurrent != m_pcEnd) && (*m_pcCurrent != TXT('>')) )
	{
		// Declarations?
		if (*m_pcCurrent == TXT('['))
		{
			++m_pcCurrent;

			while ( (m_pcCurrent != m_pcEnd) && (*m_pcCurrent != TXT(']')) )
				++m_pcCurrent;

			if (*m_pcCurrent == TXT(']'))
				++m_pcCurrent;
		}
		else
		{
			++m_pcCurrent;
		}
	}

	if (m_pcCurrent == m_pcEnd)
		throw IOException(TXT("EOF encountered reading a document type node"));

	ASSERT(*m_pcCurrent == TXT('>'));
	++m_pcCurrent;

	const tchar* pcNodeEnd = m_pcCurrent;
	size_t       nLength   = pcNodeEnd - pcNodeBegin;

	// Must be at least "<!DOCTYPE>"
	if ( (nLength < 10)
	  || (tstrncmp(pcNodeBegin, TXT("<!DOCTYPE"), 9) != 0) )
	{
		throw IOException(TXT("Invalid document type node format"));
	}

	// Keeping document type declarations?
	if ((m_nFlags & DISCARD_DOC_TYPES) == 0)
	{
		// Adjust iterators for the inner text.
		pcNodeBegin += 9;
		pcNodeEnd   -= 1;

		// Create node and append to collection.
		DocTypeNodePtr pNode = DocTypeNodePtr(new DocTypeNode(tstring(pcNodeBegin, pcNodeEnd)));
		
		AppendChild(m_oNodeStack.top(), pNode);
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read and parse CDATA section.

void Reader::ReadCDataSection(const tchar* pcNodeBegin)
{
	ASSERT((m_pcCurrent-pcNodeBegin) >= 2);

	// Find node terminator.
	while ( (m_pcCurrent != m_pcEnd) && ((*m_pcCurrent != TXT('>') || (tstrncmp(m_pcCurrent-2, TXT("]]>"), 3) != 0))) )
		++m_pcCurrent;

	if (m_pcCurrent == m_pcEnd)
		throw IOException(TXT("EOF encountered reading a CDATA section"));

	ASSERT(*m_pcCurrent == TXT('>'));
	++m_pcCurrent;

	const tchar* pcNodeEnd = m_pcCurrent;
	size_t       nLength   = pcNodeEnd - pcNodeBegin;

	// Must be at least "<![CDATA[]]>"
	if ( (nLength < 12)
	  || (tstrncmp(pcNodeBegin, TXT("<![CDATA["), 9) != 0)
	  || (tstrncmp(pcNodeEnd-3, TXT("]]>"),       3) != 0) )
	{
		throw IOException(TXT("Invalid CDATA section format"));
	}

	// Adjust iterators for the inner text.
	pcNodeBegin += 9;
	pcNodeEnd   -= 3;

	// Create node and append to collection.
	CDataNodePtr pNode = CDataNodePtr(new CDataNode(tstring(pcNodeBegin, pcNodeEnd)));
	
	AppendChild(m_oNodeStack.top(), pNode);
}

////////////////////////////////////////////////////////////////////////////////
//! Read an identifier.

const tchar* Reader::ReadIdentifier(const tchar* pcBegin, const tchar* pcEnd, tstring& strIdentifier)
{
	if (pcBegin == pcEnd)
		throw IOException(TXT("EOF encountered reading a tag identifier"));

	const tchar* pcCurrent = pcBegin;

	// Find end of identifier.
	while ( (pcCurrent != pcEnd) && (s_oCharTable.IsIdentifier(*pcCurrent)) )
		++pcCurrent;

	size_t nLength = pcCurrent - pcBegin;

	if (nLength == 0)
		throw IOException(TXT("Tag identifer missing"));

	// Extract identifier.
	strIdentifier = tstring(pcBegin, pcCurrent);

	return pcCurrent;
}

////////////////////////////////////////////////////////////////////////////////
//! Read an attribute. The reads both the name and value.

const tchar* Reader::ReadAttribute(const tchar* pcBegin, const tchar* pcEnd, tstring& strName, tstring& strValue)
{
	if (pcBegin == pcEnd)
		throw IOException(TXT("EOF encountered reading an attribute"));

	const tchar* pcCurrent = pcBegin;

	// Find end of attribute name.
	while ( (pcCurrent != pcEnd) && (s_oCharTable.IsIdentifier(*pcCurrent)) )
		++pcCurrent;

	size_t nNameLen = pcCurrent - pcBegin;

	if (nNameLen == 0)
		throw IOException(TXT("Attribute name missing"));

	// Extract attribute name.
	strName = tstring(pcBegin, pcCurrent);

	// Skip whitespace.
	while ( (pcCurrent != pcEnd) && (s_oCharTable.IsWhitespace(*pcCurrent)) )
		++pcCurrent;

	if ( (pcCurrent == pcEnd) || (*pcCurrent != TXT('=')) )
		throw IOException(TXT("EOF encountered reading an attribute"));

	++pcCurrent;

	// Skip whitespace.
	while ( (pcCurrent != pcEnd) && (s_oCharTable.IsWhitespace(*pcCurrent)) )
		++pcCurrent;

	if ( (pcCurrent == pcEnd) || ((*pcCurrent != TXT('\"')) && (*pcCurrent != TXT('\''))) )
		throw IOException(TXT("EOF encountered reading an attribute value"));

	tchar cQuote = *pcCurrent++;

	pcBegin = pcCurrent;

	// Find end of attribute value.
	while ( (pcCurrent != pcEnd) && (*pcCurrent != cQuote) )
		++pcCurrent;

	if ( (pcCurrent == pcEnd) || (*pcCurrent != cQuote) )
		throw IOException(TXT("EOF encountered reading an attribute value"));

	// Extract attribute name.
	strValue = tstring(pcBegin, pcCurrent);

	++pcCurrent;

	return pcCurrent;
}

//namespace XML
}
