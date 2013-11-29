////////////////////////////////////////////////////////////////////////////////
//! \file   Writer.hpp
//! \brief  The Writer class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_WRITER_HPP
#define XML_WRITER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Document.hpp"
#include "ElementNode.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The writer to create a text stream from an XML document.

class Writer /*: private NotCopyable*/
{
public:
	//! The writing flags.
	enum Flag
	{
		DEFAULT				= 0x0000,	//!< Default flags.
		NO_FORMATTING		= 0x0001,	//!< Don't pretty print the XML.
	};

	//! The default indentation style.
	static const tchar* DEFAULT_INDENT_STYLE;
	
	//! The default line terminator.
	static const tchar* DEFAULT_TERMINATOR;
	
	//
	// Class methods.
	//

	//! Write a document to a string buffer.
	static tstring writeDocument(DocumentPtr document, uint flags = DEFAULT, const tchar* indentStyle = DEFAULT_INDENT_STYLE);

private:
	//
	// Members.
	//
	uint			m_flags;		//!< The flags to control writing.
	tstring			m_indentStyle;	//!< The string to use for indenting.
	tstring			m_buffer;		//!< The output buffer.
	uint			m_depth;		//!< The indentation depth.

	//
	// Internal methods.
	//

	//! Default constructor.
	Writer();

	//! Constructor.
	Writer(uint flags, const tchar* indent);

	//! Destructor.
	~Writer();

	//! Write a document to a string buffer.
	tstring formatDocument(DocumentPtr document);

	//! Write a container of nodes to the buffer.
	void writeContainer(const NodeContainer& container);

	//! Write the attributes to the buffer.
	void writeAttributes(const Attributes& attributes);

	//! Write an element to the buffer.
	void writeElement(ElementNodePtr element);

	// NotCopyable.
	Writer(const Writer&);
	Writer& operator=(const Writer);
};

//namespace XML
}

#endif // XML_WRITER_HPP
