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
	};
	
	//
	// Class methods.
	//

	//! Write a document to a string buffer.
	static tstring writeDocument(DocumentPtr document);

private:
	//
	// Members.
	//
	uint			m_flags;		//!< The flags to control writing.
	tstring			m_buffer;		//!< The output buffer.

	//
	// Internal methods.
	//

	//! Default constructor.
	Writer();

	//! Constructor.
	Writer(uint flags);

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
