////////////////////////////////////////////////////////////////////////////////
//! \file   ElementNode.cpp
//! \brief  The ElementNode class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ElementNode.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

ElementNode::ElementNode()
	: NodeContainer(this)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from the element name.

ElementNode::ElementNode(const tstring& strName)
	: NodeContainer(this)
	, m_strName(strName)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from an element name and attributes.

ElementNode::ElementNode(const tstring& strName, const Attributes& vAttribs)
	: NodeContainer(this)
	, m_strName(strName)
	, m_vAttribs(vAttribs)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ElementNode::~ElementNode()
{
}

//namespace XML
}
