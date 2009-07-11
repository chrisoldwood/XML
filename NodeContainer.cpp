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

NodeContainer::NodeContainer(Node* pParent)
	: m_pParent(pParent)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

NodeContainer::~NodeContainer()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Append a child node.

void NodeContainer::appendChild(NodePtr& pNode)
{
	// Validate node.
	if (pNode->type() == DOCUMENT_NODE)
		throw Core::InvalidArgException(TXT("Failed to append a node because it's a Document node"));

	if (pNode->hasParent())
		throw Core::InvalidArgException(Core::fmt(TXT("Failed to append a '%s' node because it is already part of a document"), pNode->typeStr()));

	// Add to the children.
	m_vChildNodes.push_back(pNode);

	pNode->setParent(m_pParent);
}

//namespace XML
}
