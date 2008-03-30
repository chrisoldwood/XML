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
	: m_pParent(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Node::~Node()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Convert the node type to a string.

const tchar* Node::FormatNodeType(NodeType eType)
{
	switch(eType)
	{
		case DOCUMENT_NODE:		return TXT("Dcoument");
		case ELEMENT_NODE:		return TXT("Element");
		case TEXT_NODE:			return TXT("Text");
		case COMMENT_NODE:		return TXT("Comment");
		case PROCESSING_NODE:	return TXT("Processing Instruction");
	}

	throw Core::InvalidArgException(Core::Fmt(TXT("Invalid NodeType passed to GetNodeTypeStr: %u"), eType));
}

//namespace XML
}
