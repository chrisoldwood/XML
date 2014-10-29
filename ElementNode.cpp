////////////////////////////////////////////////////////////////////////////////
//! \file   ElementNode.cpp
//! \brief  The ElementNode class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ElementNode.hpp"
#include "TextNode.hpp"

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
//! Construction from an element name and single attribute.

ElementNode::ElementNode(const tstring& name_, AttributePtr attribute)
	: NodeContainer(this)
	, m_name(name_)
	, m_attributes(attribute)
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
//! Construction from an element name and a range of child nodes.

ElementNode::ElementNode(const tstring& name_, NodePtr* begin, NodePtr* end)
	: NodeContainer(this)
	, m_name(name_)
{
	for (NodePtr* it = begin; it != end; ++it)
		appendChild(*it);
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ElementNode::~ElementNode()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Get the child text node value if it exists.

tstring ElementNode::getTextValue() const
{
	if (getChildCount() == 0)
		return TXT("");

	if (getChildCount() != 1)
		throw Core::BadLogicException(TXT("Can't retrieve text value when more than 1 child node exists"));

	NodePtr child = getChild(0);

	if (child->type() != TEXT_NODE)
		throw Core::BadLogicException(TXT("Can't retrieve text value when child not a text node"));

	return Core::dynamic_ptr_cast<TextNode>(child)->text();
}

////////////////////////////////////////////////////////////////////////////////
//! Find the first element node matching the given name.

Core::RefCntPtr<ElementNode> ElementNode::findFirstElement(const tstring& name_) const
{
	for (const_iterator it = beginChild(); it != endChild(); ++it)
	{
		ElementNodePtr element = Core::dynamic_ptr_cast<ElementNode>(*it);

		if ( (!element.empty()) && (element->name() == name_) )
			return element;
	}

	return ElementNodePtr();
}

//namespace XML
}
