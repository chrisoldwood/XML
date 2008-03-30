////////////////////////////////////////////////////////////////////////////////
//! \file   Node.hpp
//! \brief  The Node class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_NODE_HPP
#define XML_NODE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Types.hpp"
#include <Core/RefCntPtr.hpp>

namespace XML
{

// Forward declarations.
class Node;

//! The default Node smart-pointer type.
typedef Core::RefCntPtr<Node> NodePtr;

////////////////////////////////////////////////////////////////////////////////
//! The base class for all nodes that are stored in an XML document.
//! The node types use internal reference counting to make it more efficient and
//! easier to deal with the back pointers. We store the parent node as a raw
//! pointer to ensure we don't have any cyclic references.

class Node : public Core::RefCounted
{
public:
	//
	// Properties.
	//

	//! Get the real type of the node.
	virtual NodeType Type() const = 0;

	//! Get the type of the node as a string.
	const tchar* TypeStr() const;

	//! Get if the node has a parent.
	bool HasParent() const;

	//! Get the parent node.
	const NodePtr Parent() const;

	//! Get the parent node.
	NodePtr Parent();

	//
	// Class Methods.
	//

	//! Convert the node type to a string.
	static const tchar* FormatNodeType(NodeType eType);

protected:	
	//! Default constructor.
	Node();

	//! Destructor.
	virtual ~Node();

	//
	// Properties.
	//

	//! Set the parent node.
	void SetParent(Node* pParent);

private:
	//
	// Members.
	//
	Node*	m_pParent;		//!< The parent node.

	//
	// Friends.
	//

	//! Allow container class to set the parent.
	friend class NodeContainer;
};

////////////////////////////////////////////////////////////////////////////////
//! Get the type of the node as a string.

inline const tchar* Node::TypeStr() const
{
	return FormatNodeType(Type());
}

////////////////////////////////////////////////////////////////////////////////
//! Get if the node has a parent.

inline bool Node::HasParent() const
{
	return (m_pParent != nullptr);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the parent node.

inline const NodePtr Node::Parent() const
{
	return NodePtr(m_pParent);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the parent node.

inline NodePtr Node::Parent()
{
	return NodePtr(m_pParent);
}

////////////////////////////////////////////////////////////////////////////////
//! Set the parent node.

inline void Node::SetParent(Node* pParent)
{
	ASSERT(m_pParent == nullptr);

	m_pParent = pParent;
}

//namespace XML
}

#endif // XML_NODE_HPP
