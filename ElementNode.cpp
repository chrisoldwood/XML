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
	, m_name()
	, m_attributes()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from the element name.

ElementNode::ElementNode(const tstring& name_)
	: NodeContainer(this)
	, m_name(name_)
	, m_attributes()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from an element name and attributes.

ElementNode::ElementNode(const tstring& name_, const Attributes& attributes)
	: NodeContainer(this)
	, m_name(name_)
	, m_attributes(attributes)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ElementNode::~ElementNode()
{
}

//namespace XML
}
