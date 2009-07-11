////////////////////////////////////////////////////////////////////////////////
//! \file   Document.cpp
//! \brief  The Document class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Document.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Document::Document()
	: NodeContainer(this)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Document::~Document()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Checks if the document has a root element.

bool Document::hasRootElement() const
{
	// Find the first element node...
	for (Nodes::const_iterator it = beginChild(); it != endChild(); ++it)
	{
		const NodePtr& pNode = *it;

		if (pNode->type() == ELEMENT_NODE)
			return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the root element.

const ElementNodePtr Document::getRootElement() const
{
	// Find the first element node...
	for (Nodes::const_iterator it = beginChild(); it != endChild(); ++it)
	{
		NodePtr pNode = *it;

		if (pNode->type() == ELEMENT_NODE)
			return Core::static_ptr_cast<ElementNode>(pNode);
	}

	return ElementNodePtr();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the root element.

ElementNodePtr Document::getRootElement()
{
	// Find the first element node...
	for (Nodes::const_iterator it = beginChild(); it != endChild(); ++it)
	{
		NodePtr pNode = *it;

		if (pNode->type() == ELEMENT_NODE)
			return Core::static_ptr_cast<ElementNode>(pNode);
	}

	return ElementNodePtr();
}

//namespace XML
}
