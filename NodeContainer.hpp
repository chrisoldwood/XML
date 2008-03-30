////////////////////////////////////////////////////////////////////////////////
//! \file   NodeContainer.hpp
//! \brief  The NodeContainer class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_NODECONTAINER_HPP
#define XML_NODECONTAINER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Node.hpp"

namespace XML
{

//! The default container type for a collection of Nodes.
typedef std::vector<NodePtr> Nodes;

////////////////////////////////////////////////////////////////////////////////
//! The mixin class used for node types that can contain other nodes. The outer
//! parent node is held internally so that we can fix up the child nodes here
//! automatically.

class NodeContainer
{
public:
	//
	// Properties.
	//

	//! Query if the node has any child nodes.
	bool HasChildren() const;

	//! Get the count of child nodes.
	size_t GetChildCount() const;
	
	//! Get the start iterator for the child nodes.
	Nodes::const_iterator BeginChild() const;

	//! Get the end iterator for the child nodes.
	Nodes::const_iterator EndChild() const;

	//! Get the start iterator for the child nodes.
	Nodes::iterator BeginChild();

	//! Get the end iterator for the child nodes.
	Nodes::iterator EndChild();

	//
	// Methods.
	//

	//! Append a child node.
	void AppendChild(NodePtr& pNode);

	//! Append a child node.
	template<typename T>
	void AppendChild(Core::RefCntPtr<T>& pNode);

protected:
	//! Constructor.
	NodeContainer(Node* pParent);

	//! Destructor.
	virtual ~NodeContainer();

private:
	//
	// Members.
	//
	Node*	m_pParent;			//!< The outer parent node.
	Nodes	m_vChildNodes;		//!< The collection of child nodes.
};

////////////////////////////////////////////////////////////////////////////////
//! Query if the node has any child nodes.

inline bool NodeContainer::HasChildren() const
{
	return !m_vChildNodes.empty();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the count of child nodes.

inline size_t NodeContainer::GetChildCount() const
{
	return m_vChildNodes.size();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the start iterator for the child nodes.

inline Nodes::const_iterator NodeContainer::BeginChild() const
{
	return m_vChildNodes.begin();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the end iterator for the child nodes.

inline Nodes::const_iterator NodeContainer::EndChild() const
{
	return m_vChildNodes.end();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the start iterator for the child nodes.

inline Nodes::iterator NodeContainer::BeginChild()
{
	return m_vChildNodes.begin();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the end iterator for the child nodes.

inline Nodes::iterator NodeContainer::EndChild()
{
	return m_vChildNodes.end();
}

//! Append a child node.
template<typename T>
inline void NodeContainer::AppendChild(Core::RefCntPtr<T>& pNode)
{
	NodePtr p = pNode;

	AppendChild(p);
}

//namespace XML
}

#endif // XML_NODECONTAINER_HPP
