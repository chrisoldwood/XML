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

	//! Construction from an element name and attributes.
	ElementNode(const tstring& name, const Attributes& attributes);

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

//namespace XML
}

#endif // XML_ELEMENTNODE_HPP
