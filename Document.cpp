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

bool Document::HasRootElement() const
{
	// Find the first element node...
	for (Nodes::const_iterator it = BeginChild(); it != EndChild(); ++it)
	{
		const NodePtr& pNode = *it;

		if (pNode->Type() == ELEMENT_NODE)
			return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the root element.

const ElementNodePtr Document::GetRootElement() const
{
	// Find the first element node...
	for (Nodes::const_iterator it = BeginChild(); it != EndChild(); ++it)
	{
		NodePtr pNode = *it;

		if (pNode->Type() == ELEMENT_NODE)
			return Core::static_ptr_cast<ElementNode>(pNode);
	}

	return ElementNodePtr();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the root element.

ElementNodePtr Document::GetRootElement()
{
	// Find the first element node...
	for (Nodes::const_iterator it = BeginChild(); it != EndChild(); ++it)
	{
		NodePtr pNode = *it;

		if (pNode->Type() == ELEMENT_NODE)
			return Core::static_ptr_cast<ElementNode>(pNode);
	}

	return ElementNodePtr();
}

//namespace XML
}
