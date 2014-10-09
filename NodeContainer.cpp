////////////////////////////////////////////////////////////////////////////////
//! \file   NodeContainer.cpp
//! \brief  The NodeContainer class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "NodeContainer.hpp"
#include <Core/InvalidArgException.hpp>
#include <Core/StringUtils.hpp>

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

NodeContainer::NodeContainer(Node* parent)
	: m_parent(parent)
	, m_childNodes()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

NodeContainer::~NodeContainer()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Get a child by its index.

NodePtr NodeContainer::getChild(size_t index) const
{
	if (index >= m_childNodes.size())
		throw Core::InvalidArgException(Core::fmt(TXT("Invalid child node index '%u'"), index));

	return m_childNodes[index];
}

////////////////////////////////////////////////////////////////////////////////
//! Append a child node.

void NodeContainer::appendChild(NodePtr& node)
{
	// Validate node.
	if (node->type() == DOCUMENT_NODE)
		throw Core::InvalidArgException(TXT("Failed to append a node because it's a Document node"));

	if (node->hasParent())
		throw Core::InvalidArgException(Core::fmt(TXT("Failed to append a '%s' node because it is already part of a document"), node->typeStr()));

	// Add to the children.
	m_childNodes.push_back(node);

	node->setParent(m_parent);
}

//namespace XML
}
