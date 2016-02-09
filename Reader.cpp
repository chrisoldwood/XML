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
static CharTable s_charTable;

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Reader::Reader()
	: m_begin(nullptr)
	, m_end(nullptr)
	, m_current(nullptr)
	, m_flags(DEFAULT)
	, m_stack()
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
inline void appendChild(NodePtr parent, Core::RefCntPtr<T>& child)
{
	ASSERT((parent->type() == DOCUMENT_NODE) || (parent->type() == ELEMENT_NODE));

	if (parent->type() == DOCUMENT_NODE)
		Core::static_ptr_cast<Document>(parent)->appendChild(child);
	else
		Core::static_ptr_cast<ElementNode>(parent)->appendChild(child);
}

////////////////////////////////////////////////////////////////////////////////
//! Read a document from a string.

DocumentPtr Reader::parseDocument(const tstring& string, uint flags)
{
	const tchar* begin = nullptr;
	const tchar* end   = nullptr;

	// Get raw iterators for the string.
	if (!string.empty())
	{
		begin = string.data();
		end   = begin + string.length();
	}

	return readDocument(begin, end, flags);
}

////////////////////////////////////////////////////////////////////////////////
//! Read a document from a pair of raw string pointers.

DocumentPtr Reader::parseDocument(const tchar* begin, const tchar* end, uint flags)
{
	initialise(begin, end, flags);

	DocumentPtr document(new Document);

	// Start by appending to the document node.
	m_stack.push(document);

	// For all nodes...
	while (m_current != m_end)
	{
		const tchar* nodeBegin = m_current;

		// Is a tag?
		if (*m_current == TXT('<'))
		{
			++m_current;

			// A comment or document type tag?
			if (*m_current == TXT('!'))
			{
				if (m_current != m_end)
				{
					++m_current;

					if (*m_current == TXT('-'))
					{
						readCommentTag(nodeBegin);
					}
					else if (*m_current == TXT('D'))
					{
						readDocTypeTag(nodeBegin);
					}
					else if (*m_current == TXT('['))
					{
						readCDataSection(nodeBegin);
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
			else if (*m_current == TXT('?'))
			{
				readProcessingTag(nodeBegin);
			}
			// An element tag.
			else
			{
				readElementTag(nodeBegin);
			}
		}
		// Is text.
		else
		{
			readTextNode(nodeBegin);
		}
	}

	// Missing one or more end tags?
	if (m_stack.size() > 1)
		throw IOException(TXT("One or more end tags were missing"));

	m_stack.pop();

	// Document empty?
	if (!document->hasRootElement())
		throw IOException(TXT("The XML document was empty"));

	ASSERT(m_stack.size() == 0);

	return document;
}

////////////////////////////////////////////////////////////////////////////////
//! Read a document from a pair of raw string pointers.

DocumentPtr Reader::readDocument(const tchar* begin, const tchar* end, uint flags)
{
	XML::Reader reader;

	return reader.parseDocument(begin, end, flags);
}

////////////////////////////////////////////////////////////////////////////////
//! Read a document from a string.

DocumentPtr Reader::readDocument(const tstring& string, uint flags)
{
	XML::Reader reader;

	return reader.parseDocument(string, flags);
}

////////////////////////////////////////////////////////////////////////////////
//! Initialise the internal state ready for reading.

void Reader::initialise(const tchar* begin, const tchar* end, uint flags)
{
	m_begin   = begin;
	m_end     = end;
	m_current = begin;
	m_flags   = flags;

	while (!m_stack.empty())
		m_stack.pop();
}

////////////////////////////////////////////////////////////////////////////////
//! Read and parse a comment tag.

void Reader::readCommentTag(const tchar* nodeBegin)
{
	ASSERT((m_current-nodeBegin) >= 2);

	// Find node terminator.
	while ( (m_current != m_end) && ((*m_current != TXT('>') || (tstrncmp(m_current-2, TXT("-->"), 3) != 0))) )
		++m_current;

	if (m_current == m_end)
		throw IOException(TXT("EOF encountered reading a comment node"));

	ASSERT(*m_current == TXT('>'));
	++m_current;

	const tchar* nodeEnd = m_current;
	size_t       length  = nodeEnd - nodeBegin;

	// Must be at least "<!---->"
	if ( (length < 7)
	  || (tstrncmp(nodeBegin, TXT("<!--"), 4) != 0)
	  || (tstrncmp(nodeEnd-3, TXT("-->"),  3) != 0) )
	{
		throw IOException(TXT("Invalid comment node format"));
	}

	// Keeping comments?
	if ((m_flags & DISCARD_COMMENTS) == 0)
	{
		// Adjust iterators for the inner text.
		nodeBegin += 4;
		nodeEnd   -= 3;

		// Create node and append to collection.
		CommentNodePtr node = CommentNodePtr(new CommentNode(tstring(nodeBegin, nodeEnd)));

		appendChild(m_stack.top(), node);
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read and parse a processing instruction tag.

void Reader::readProcessingTag(const tchar* nodeBegin)
{
	// Find node terminator.
	while ( (m_current != m_end) && (*m_current != TXT('>')) )
		++m_current;

	if (m_current == m_end)
		throw IOException(TXT("EOF encountered reading a processing instruction node"));

	ASSERT(*m_current == TXT('>'));
	++m_current;

	const tchar* nodeEnd = m_current;
	size_t       length  = nodeEnd - nodeBegin;

	// Must be at least "<?_?>"
	if ( (length < 5)
	  || (tstrncmp(nodeBegin, TXT("<?"), 2) != 0)
	  || (tstrncmp(nodeEnd-2, TXT("?>"), 2) != 0) )
	{
		throw IOException(TXT("Invalid processing instruction node format"));
	}

	// Keeping processing instructions?
	if ((m_flags & DISCARD_PROC_INSTNS) == 0)
	{
		// Adjust iterators for the inner text.
		nodeBegin += 2;
		nodeEnd   -= 2;

		tstring    target;
		Attributes attributes;

		// Read the target.
		const tchar* current = readIdentifier(nodeBegin, nodeEnd, target);

		while (current != nodeEnd)
		{
			// Skip white-space.
			while ( (current != nodeEnd) && (s_charTable.isWhitespace(*current)) )
				++current;

			// Read attribute, if present.
			if (current != nodeEnd)
			{
				tstring name, value;

				current = readAttribute(current, nodeEnd, name, value);

				attributes.set(AttributePtr(new Attribute(name, value)));
			}
		}

		// Create node and append to collection.
		ProcessingNodePtr node = ProcessingNodePtr(new ProcessingNode(target, attributes));

		appendChild(m_stack.top(), node);
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read and create a text node.

void Reader::readTextNode(const tchar* nodeBegin)
{
	bool whitespaceOnly = true;

	// Read up to a tag marker.
	while ( (m_current != m_end) && (*m_current != TXT('<')) )
	{
		if (!tisspace(static_cast<utchar>(*m_current)))
			whitespaceOnly = false;

		++m_current;
	}

	const tchar* nodeEnd = m_current;

	// Append text node, if present.
	if (nodeBegin != nodeEnd)
	{
		// Disallow text outside the root element.
		if ( (!whitespaceOnly) && (m_stack.size() == 1) )
			throw IOException(TXT("Non-whitespace character(s) outside the root element"));

		// Not just white-space OR we're keeping white-space?
		if (!whitespaceOnly || ((m_flags & DISCARD_WHITESPACE) == 0))
		{
			// Create node and append to collection.
			TextNodePtr node = TextNodePtr(new TextNode(tstring(nodeBegin, nodeEnd)));

			appendChild(m_stack.top(), node);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read and parse an element tag. If the tag is a start tag or empty tag an
//! element node is returned. If it's a close tag, no node is returned.

void Reader::readElementTag(const tchar* nodeBegin)
{
	// Find node terminator.
	while ( (m_current != m_end) && (*m_current != TXT('>')) )
	{
		// Apostrophe enclosed string?
		if (*m_current == TXT('\''))
		{
			++m_current;

			while ( (m_current != m_end) && (*m_current != TXT('\'')) )
				++m_current;

			if (*m_current == TXT('\''))
				++m_current;
		}
		// Double-quote enclosed string?
		else if (*m_current == TXT('\"'))
		{
			++m_current;

			while ( (m_current != m_end) && (*m_current != TXT('\"')) )
				++m_current;

			if (*m_current == TXT('\"'))
				++m_current;
		}
		else
		{
			++m_current;
		}
	}

	if (m_current == m_end)
		throw IOException(TXT("EOF encountered reading an element node"));

	ASSERT(*m_current == TXT('>'));
	++m_current;

	const tchar* nodeEnd = m_current;
	size_t       length  = nodeEnd - nodeBegin;

	// Must be at least "<X>"
	if (length < 3)
		throw IOException(TXT("Invalid element node format"));

	// Is the end of an element?
	if (*(nodeBegin+1) == TXT('/'))
	{
		// Adjust iterators for the inner text.
		nodeBegin += 2;
		nodeEnd   -= 1;

		tstring name(nodeBegin, nodeEnd);

		ASSERT(!m_stack.empty());

		// Validate tag matches the last open one.
		NodePtr node = m_stack.top();

		if (node->type() != ELEMENT_NODE)
			throw IOException(TXT("End tag encountered without a matching start tag"));

		ElementNodePtr element = Core::static_ptr_cast<ElementNode>(node);

		if (element->name() != name)
			throw IOException(TXT("End tag does not match the last start tag"));

		// Valid.
		m_stack.pop();
	}
	// Is an open or empty element.
	else
	{
		// Adjust iterators for the inner text.
		nodeBegin += 1;

		if (*(nodeEnd-2) == TXT('/'))
			nodeEnd -= 2;
		else
			nodeEnd -= 1;

		tstring    elementName;
		Attributes attributes;

		// Read the target.
		const tchar* current = readIdentifier(nodeBegin, nodeEnd, elementName);

		while (current != nodeEnd)
		{
			// Skip white-space.
			while ( (current != nodeEnd) && (s_charTable.isWhitespace(*current)) )
				++current;

			// Read attribute, if present.
			if (current != nodeEnd)
			{
				tstring attribName, attribValue;

				current = readAttribute(current, nodeEnd, attribName, attribValue);

				attributes.set(AttributePtr(new Attribute(attribName, attribValue)));
			}
		}

		// Create node and append to collection.
		ElementNodePtr node(new ElementNode(elementName, attributes));

		appendChild(m_stack.top(), node);

		// Track start tags.
		if (*nodeEnd != TXT('/'))
			m_stack.push(node);
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read and parse a document type tag.

void Reader::readDocTypeTag(const tchar* nodeBegin)
{
	// Find node terminator.
	while ( (m_current != m_end) && (*m_current != TXT('>')) )
	{
		// Declarations?
		if (*m_current == TXT('['))
		{
			++m_current;

			while ( (m_current != m_end) && (*m_current != TXT(']')) )
				++m_current;

			if (*m_current == TXT(']'))
				++m_current;
		}
		else
		{
			++m_current;
		}
	}

	if (m_current == m_end)
		throw IOException(TXT("EOF encountered reading a document type node"));

	ASSERT(*m_current == TXT('>'));
	++m_current;

	const tchar* nodeEnd = m_current;
	size_t       length  = nodeEnd - nodeBegin;

	// Must be at least "<!DOCTYPE>"
	if ( (length < 10)
	  || (tstrncmp(nodeBegin, TXT("<!DOCTYPE"), 9) != 0) )
	{
		throw IOException(TXT("Invalid document type node format"));
	}

	// Keeping document type declarations?
	if ((m_flags & DISCARD_DOC_TYPES) == 0)
	{
		// Adjust iterators for the inner text.
		nodeBegin += 9;
		nodeEnd   -= 1;

		// Create node and append to collection.
		DocTypeNodePtr node = DocTypeNodePtr(new DocTypeNode(tstring(nodeBegin, nodeEnd)));

		appendChild(m_stack.top(), node);
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Read and parse CDATA section.

void Reader::readCDataSection(const tchar* nodeBegin)
{
	ASSERT((m_current-nodeBegin) >= 2);

	// Find node terminator.
	while ( (m_current != m_end) && ((*m_current != TXT('>') || (tstrncmp(m_current-2, TXT("]]>"), 3) != 0))) )
		++m_current;

	if (m_current == m_end)
		throw IOException(TXT("EOF encountered reading a CDATA section"));

	ASSERT(*m_current == TXT('>'));
	++m_current;

	const tchar* nodeEnd = m_current;
	size_t       length  = nodeEnd - nodeBegin;

	// Must be at least "<![CDATA[]]>"
	if ( (length < 12)
	  || (tstrncmp(nodeBegin, TXT("<![CDATA["), 9) != 0)
	  || (tstrncmp(nodeEnd-3, TXT("]]>"),       3) != 0) )
	{
		throw IOException(TXT("Invalid CDATA section format"));
	}

	// Adjust iterators for the inner text.
	nodeBegin += 9;
	nodeEnd   -= 3;

	// Create node and append to collection.
	CDataNodePtr node = CDataNodePtr(new CDataNode(tstring(nodeBegin, nodeEnd)));

	appendChild(m_stack.top(), node);
}

////////////////////////////////////////////////////////////////////////////////
//! Read an identifier.

const tchar* Reader::readIdentifier(const tchar* begin, const tchar* end, tstring& identifier)
{
	if (begin == end)
		throw IOException(TXT("EOF encountered reading a tag identifier"));

	const tchar* current = begin;

	// Find end of identifier.
	while ( (current != end) && (s_charTable.isIdentifier(*current)) )
		++current;

	size_t length = current - begin;

	if (length == 0)
		throw IOException(TXT("Tag identifier missing"));

	// Extract identifier.
	identifier = tstring(begin, current);

	return current;
}

////////////////////////////////////////////////////////////////////////////////
//! Read an attribute. The reads both the name and value.

const tchar* Reader::readAttribute(const tchar* begin, const tchar* end, tstring& name, tstring& value)
{
	if (begin == end)
		throw IOException(TXT("EOF encountered reading an attribute"));

	const tchar* current = begin;

	// Find end of attribute name.
	while ( (current != end) && (s_charTable.isIdentifier(*current)) )
		++current;

	size_t nameLen = current - begin;

	if (nameLen == 0)
		throw IOException(TXT("Attribute name missing"));

	// Extract attribute name.
	name = tstring(begin, current);

	// Skip white-space.
	while ( (current != end) && (s_charTable.isWhitespace(*current)) )
		++current;

	if ( (current == end) || (*current != TXT('=')) )
		throw IOException(TXT("EOF encountered reading an attribute"));

	++current;

	// Skip white-space.
	while ( (current != end) && (s_charTable.isWhitespace(*current)) )
		++current;

	if ( (current == end) || ((*current != TXT('\"')) && (*current != TXT('\''))) )
		throw IOException(TXT("EOF encountered reading an attribute value"));

	tchar quote = *current++;

	begin = current;

	// Find end of attribute value.
	while ( (current != end) && (*current != quote) )
		++current;

	if ( (current == end) || (*current != quote) )
		throw IOException(TXT("EOF encountered reading an attribute value"));

	// Extract attribute name.
	value = tstring(begin, current);

	++current;

	return current;
}

//namespace XML
}
