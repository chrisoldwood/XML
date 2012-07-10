////////////////////////////////////////////////////////////////////////////////
//! \file   Node.cpp
//! \brief  The Node class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Node.hpp"
#include <Core/InvalidArgException.hpp>
#include <Core/StringUtils.hpp>

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Node::Node()
	: m_parent(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Node::~Node()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Convert the node type to a string.

const tchar* Node::formatNodeType(NodeType type)
{
	switch(type)
	{
		case DOCUMENT_NODE:		return TXT("Document");
		case ELEMENT_NODE:		return TXT("Element");
		case TEXT_NODE:			return TXT("Text");
		case COMMENT_NODE:		return TXT("Comment");
		case PROCESSING_NODE:	return TXT("Processing Instruction");
		case DOCTYPE_NODE:		return TXT("Document Type");
		case CDATA_NODE:		return TXT("CDATA");
		default:				ASSERT_FALSE();
	}

	throw Core::InvalidArgException(Core::fmt(TXT("Invalid NodeType passed to GetNodeTypeStr: %u"), type));
}

//namespace XML
}
