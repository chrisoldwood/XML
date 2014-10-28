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
#include <vector>
#include <Core/BadLogicException.hpp>

namespace XML
{

//! The default container type for a collection of Nodes.
typedef std::vector<NodePtr> Nodes;

////////////////////////////////////////////////////////////////////////////////
//! The mixin class used for node types that can contain other nodes. The outer
//! parent node is held internally so that we can fix up the child nodes here
//! automatically.

class NodeContainer /*: private NotCopyable*/
{
public:
	//! The container const iterator.
	typedef Nodes::const_iterator const_iterator;
	//! The container iterator.
	typedef Nodes::iterator iterator;

	//
	// Properties.
	//

	//! Query if the node has any child nodes.
	bool hasChildren() const;

	//! Get the count of child nodes.
	size_t getChildCount() const;

	//! Get a child by its index.
	NodePtr getChild(size_t index) const;

	//! Get a child by its index.
	template<typename T>
	Core::RefCntPtr<T> getChild(size_t index) const;

	//! Get the start iterator for the child nodes.
	const_iterator beginChild() const;

	//! Get the end iterator for the child nodes.
	const_iterator endChild() const;

	//! Get the start iterator for the child nodes.
	iterator beginChild();

	//! Get the end iterator for the child nodes.
	iterator endChild();

	//
	// Methods.
	//

	//! Append a child node.
	void appendChild(NodePtr& node);

	//! Append a child node.
	template<typename T>
	void appendChild(Core::RefCntPtr<T> node);

protected:
	//! Constructor.
	NodeContainer(Node* parent);

	//! Destructor.
	virtual ~NodeContainer();

private:
	//
	// Members.
	//
	Node*	m_parent;			//!< The outer parent node.
	Nodes	m_childNodes;		//!< The collection of child nodes.

	// NotCopyable.
	NodeContainer(const NodeContainer&);
	NodeContainer& operator=(const NodeContainer);
};

////////////////////////////////////////////////////////////////////////////////
//! Query if the node has any child nodes.

inline bool NodeContainer::hasChildren() const
{
	return !m_childNodes.empty();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the count of child nodes.

inline size_t NodeContainer::getChildCount() const
{
	return m_childNodes.size();
}

////////////////////////////////////////////////////////////////////////////////
//! Get a child by its index.

template<typename T>
inline Core::RefCntPtr<T> NodeContainer::getChild(size_t index) const
{
	Core::RefCntPtr<T> node = Core::dynamic_ptr_cast<T>(getChild(index));

	if (node.get() == nullptr)
		throw Core::BadLogicException(TXT("Failed to downcast node type"));

	return node;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the start iterator for the child nodes.

inline NodeContainer::const_iterator NodeContainer::beginChild() const
{
	return m_childNodes.begin();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the end iterator for the child nodes.

inline NodeContainer::const_iterator NodeContainer::endChild() const
{
	return m_childNodes.end();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the start iterator for the child nodes.

inline NodeContainer::iterator NodeContainer::beginChild()
{
	return m_childNodes.begin();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the end iterator for the child nodes.

inline NodeContainer::iterator NodeContainer::endChild()
{
	return m_childNodes.end();
}

//! Append a child node.
template<typename T>
inline void NodeContainer::appendChild(Core::RefCntPtr<T> node)
{
	NodePtr p = node;

	appendChild(p);
}

//namespace XML
}

#endif // XML_NODECONTAINER_HPP
