////////////////////////////////////////////////////////////////////////////////
//! \file   ElementNode.hpp
//! \brief  The ElementNode class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_ELEMENTNODE_HPP
#define XML_ELEMENTNODE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Node.hpp"
#include "NodeContainer.hpp"
#include "Attributes.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The XML node type used to denote an element. An element is a container node
//! that has both attributes and other child nodes.

class ElementNode : public Node, public NodeContainer
{
public:
	//! Default constructor.
	ElementNode();

	//! Construction from the element name.
	ElementNode(const tstring& name);

	//! Construction from an element name and single attribute.
	ElementNode(const tstring& name, AttributePtr attribute);

	//! Construction from an element name and attributes.
	ElementNode(const tstring& name, const Attributes& attributes);

	//! Construction from an element name and single child node.
	template<typename T>
	ElementNode(const tstring& name, Core::RefCntPtr<T> childNode);

	//! Construction from an element name and a range of child nodes.
	ElementNode(const tstring& name, NodePtr* begin, NodePtr* end);

	//
	// Properties
	//

	//! Get the real type of the node.
	virtual NodeType type() const;

	//! Get the elements name.
	const tstring& name() const;

	//! Set the elements name.
	void setName(const tstring& name);

	//! Get the attributes.
	const Attributes& getAttributes() const;

	//! Get the attributes.
	Attributes& getAttributes();

	//
	// Methods
	//

	//! Set an attribute from a name/value pair.
	void setAttribute(const tstring& name, const tstring& value);

	//! Get the value of an attribute by name or throw if not found.
	const tstring& getAttributeValue(const tstring& name) const; // throw(InvalidArgException)

	//! Get the child text node value if it exists.
	tstring getTextValue() const; // throw(BadLogicException)

	//! Find the first element node matching the given name.
	Core::RefCntPtr<ElementNode> findFirstElement(const tstring& name) const;

private:
	//
	// Members.
	//
	tstring		m_name;			//!< The element name.
	Attributes	m_attributes;	//!< The attributes.

	//! Destructor.
	virtual ~ElementNode();
};

//! The default ElementNode smart-pointer type.
typedef Core::RefCntPtr<ElementNode> ElementNodePtr;

////////////////////////////////////////////////////////////////////////////////
//! Construction from an element name and single child element.

template<typename T>
inline ElementNode::ElementNode(const tstring& name_, Core::RefCntPtr<T> childNode)
	: NodeContainer(this)
	, m_name(name_)
	, m_attributes()
{
	appendChild(childNode);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the real type of the node.

inline NodeType ElementNode::type() const
{
	return ELEMENT_NODE;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the elements name.

inline const tstring& ElementNode::name() const
{
	return m_name;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the elements name.

inline void ElementNode::setName(const tstring& name_)
{
	m_name = name_;
}


////////////////////////////////////////////////////////////////////////////////
//! Get the attributes.

inline const Attributes& ElementNode::getAttributes() const
{
	return m_attributes;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the attributes.

inline Attributes& ElementNode::getAttributes()
{
	return m_attributes;
}

////////////////////////////////////////////////////////////////////////////////
//! Set an attribute from a name/value pair.

inline void ElementNode::setAttribute(const tstring& name_, const tstring& value)
{
	return m_attributes.setAttribute(name_, value);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the value of an attribute by name or throw if not found.

inline const tstring& ElementNode::getAttributeValue(const tstring& name_) const
{
	return m_attributes.get(name_)->value();
}

////////////////////////////////////////////////////////////////////////////////
//! Create an empty element.

inline ElementNodePtr makeElement()
{
	return ElementNodePtr(new ElementNode());
}

////////////////////////////////////////////////////////////////////////////////
//! Create an element with a specified name.

inline ElementNodePtr makeElement(const tstring& name)
{
	return ElementNodePtr(new ElementNode(name));
}

////////////////////////////////////////////////////////////////////////////////
//! Create an element with a specified name and a single attribute.

inline ElementNodePtr makeElement(const tstring& name, AttributePtr attribute)
{
	return ElementNodePtr(new ElementNode(name, attribute));
}

////////////////////////////////////////////////////////////////////////////////
//! Create an element with a specified name and a set of attributes.

inline ElementNodePtr makeElement(const tstring& name, Attributes attributes)
{
	return ElementNodePtr(new ElementNode(name, attributes));
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from an element name and single child node.

template<typename T>
inline ElementNodePtr makeElement(const tstring& name, Core::RefCntPtr<T> childNode)
{
	return ElementNodePtr(new ElementNode(name, childNode));
}

//! Construction from an element name and a range of child nodes.
inline ElementNodePtr makeElement(const tstring& name, NodePtr* begin, NodePtr* end)
{
	return ElementNodePtr(new ElementNode(name, begin, end));
}

//namespace XML
}

#endif // XML_ELEMENTNODE_HPP
