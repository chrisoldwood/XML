////////////////////////////////////////////////////////////////////////////////
//! \file   Types.hpp
//! \brief  .
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_TYPES_HPP
#define XML_TYPES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The types of nodes stored in an XML document. This is used for doing RTTI
//! when navigating the XML document.

enum NodeType
{
	DOCUMENT_NODE,		//!< The top-most node.
	ELEMENT_NODE,		//!< An element node.
	TEXT_NODE,			//!< A text string node.
	COMMENT_NODE,		//!< A comment node.
	PROCESSING_NODE,	//!< A processing instruction node.
	DOCTYPE_NODE,		//!< A document type node.
	CDATA_NODE,			//!< A CDATA section.
};

////////////////////////////////////////////////////////////////////////////////
//! The types of tags stored in an XML stream. This is used for doing RTTI when
//! deserializing an XML stream.

enum TagType
{
};

//namespace XML
}

#endif // XML_TYPES_HPP
