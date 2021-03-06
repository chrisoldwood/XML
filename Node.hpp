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
	virtual NodeType type() const = 0;

	//! Get the type of the node as a string.
	const tchar* typeStr() const;

	//! Get if the node has a parent.
	bool hasParent() const;

	//! Get the parent node.
	const NodePtr parent() const;

	//! Get the parent node.
	NodePtr parent();

	//
	// Class Methods.
	//

	//! Convert the node type to a string.
	static const tchar* formatNodeType(NodeType type);

protected:
	//! Default constructor.
	Node();

	//! Destructor.
	virtual ~Node();

	//
	// Properties.
	//

	//! Set the parent node.
	void setParent(Node* parent);

private:
	//
	// Members.
	//
	Node*	m_parent;		//!< The parent node.

	//
	// Friends.
	//

	//! Allow container class to set the parent.
	friend class NodeContainer;

	// NotCopyable.
	Node(const Node&);
	Node& operator=(const Node&);
};

////////////////////////////////////////////////////////////////////////////////
//! Get the type of the node as a string.

inline const tchar* Node::typeStr() const
{
	return formatNodeType(type());
}

////////////////////////////////////////////////////////////////////////////////
//! Get if the node has a parent.

inline bool Node::hasParent() const
{
	return (m_parent != nullptr);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the parent node.

inline const NodePtr Node::parent() const
{
	return NodePtr(m_parent, true);
}

////////////////////////////////////////////////////////////////////////////////
//! Get the parent node.

inline NodePtr Node::parent()
{
	return NodePtr(m_parent, true);
}

////////////////////////////////////////////////////////////////////////////////
//! Set the parent node.

inline void Node::setParent(Node* parent_)
{
	ASSERT(m_parent == nullptr);

	m_parent = parent_;
}

//namespace XML
}

#endif // XML_NODE_HPP
