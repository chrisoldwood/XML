////////////////////////////////////////////////////////////////////////////////
//! \file   Reader.hpp
//! \brief  The Reader class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_READER_HPP
#define XML_READER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Document.hpp"
#include <stack>

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The reader to create an XML document from a text stream.

class Reader /*: private NotCopyable*/
{
public:
	//! Default constructor.
	Reader();

	//! Destructor.
	~Reader();

	//! The readingflags.
	enum Flag
	{
		DEFAULT				= 0x0000,	//!< Default flags.
		DISCARD_WHITESPACE	= 0x0001,	//!< Discard whitespace-only text nodes.
		DISCARD_COMMENTS	= 0x0002,	//!< Discard comment nodes.
		DISCARD_PROC_INSTNS	= 0x0004,	//!< Discard processing instructions.
		DISCARD_DOC_TYPES	= 0x0008,	//!< Discard document type declarations.
	};

	//
	// Methods.
	//

	//! Read a document from a pair of raw string pointers.
	DocumentPtr readDocument(const tchar* begin, const tchar* end, uint flags = DEFAULT); // throw(IOException)

	//! Read a document from a string.
	DocumentPtr readDocument(const tstring& string, uint flags = DEFAULT); // throw(IOException)

private:
	//! A stack of XML nodes.
	typedef std::stack<NodePtr> NodeStack;

	//
	// Members.
	//
	const tchar*	m_begin;		//!< The start of the text stream.
	const tchar*	m_end;			//!< The end of the text stream.
	const tchar*	m_current;		//!< The current position in the stream.
	uint			m_flags;		//!< The flags to control reading.
	NodeStack		m_stack;		//!< The stack of unclosed element nodes.

	//
	// Internal methods.
	//

	//! Initialise the internal state ready for reading.
	void initialise(const tchar* begin, const tchar* end, uint flags);

	//! Read and parse a comment tag.
	void readCommentTag(const tchar* nodeBegin);

	//! Read and parse a processing instruction tag.
	void readProcessingTag(const tchar* nodeBegin);

	//! Read and create a text node.
	void readTextNode(const tchar* nodeBegin);

	//! Read and parse an element tag.
	void readElementTag(const tchar* nodeBegin);

	//! Read and parse a document type tag.
	void readDocTypeTag(const tchar* nodeBegin);

	//! Read and parse CDATA section.
	void readCDataSection(const tchar* nodeBegin);

	//! Read an identifier.
	const tchar* readIdentifier(const tchar* begin, const tchar* end, tstring& identifier);

	//! Read an attribute.
	const tchar* readAttribute(const tchar* begin, const tchar* end, tstring& name, tstring& value);

	// NotCopyable.
	Reader(const Reader&);
	Reader& operator=(const Reader);
};

////////////////////////////////////////////////////////////////////////////////
//! Read a document from a string.

inline DocumentPtr Reader::readDocument(const tstring& string, uint flags)
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

//namespace XML
}

#endif // XML_READER_HPP
