////////////////////////////////////////////////////////////////////////////////
//! \file   CDataNode.cpp
//! \brief  The CDataNode class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "CDataNode.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

CDataNode::CDataNode()
	: m_text()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from the text string.

CDataNode::CDataNode(const tstring& text_)
	: m_text(text_)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

CDataNode::~CDataNode()
{
}

//namespace XML
}
