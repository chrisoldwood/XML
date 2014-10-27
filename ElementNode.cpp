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

ElementNode::ElementNode(const tstring& name)
	: NodeContainer(this)
	, m_name(name)
	, m_attributes()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from an element name and single attribute.

ElementNode::ElementNode(const tstring& name, AttributePtr attribute)
	: NodeContainer(this)
	, m_name(name)
	, m_attributes(attribute)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from an element name and attributes.

ElementNode::ElementNode(const tstring& name, const Attributes& attributes)
	: NodeContainer(this)
	, m_name(name)
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
