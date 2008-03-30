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
	ElementNode(const std::tstring& strName);

	//
	// Properties
	//

	//! Get the real type of the node.
	virtual NodeType Type() const;

	//! Get the elements name.
	const std::tstring& Name() const;

	//! Set the elements name.
	void SetName(const std::tstring& strName);

private:
	//
	// Members.
	//
	std::tstring	m_strName;		//!< The element name.

	//! Destructor.
	virtual ~ElementNode();
};

//! The default ElementNode smart-pointer type.
typedef Core::RefCntPtr<ElementNode> ElementNodePtr;

////////////////////////////////////////////////////////////////////////////////
//! Get the real type of the node.

inline NodeType ElementNode::Type() const
{
	return ELEMENT_NODE;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the elements name.

inline const std::tstring& ElementNode::Name() const
{
	return m_strName;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the elements name.

inline void ElementNode::SetName(const std::tstring& strName)
{
	m_strName = strName;
}

//namespace XML
}

#endif // XML_ELEMENTNODE_HPP
