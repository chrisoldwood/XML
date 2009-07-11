////////////////////////////////////////////////////////////////////////////////
//! \file   Document.hpp
//! \brief  The Document class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_DOCUMENT_HPP
#define XML_DOCUMENT_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Node.hpp"
#include "NodeContainer.hpp"
#include "ElementNode.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The XML node type used for the top-most node. This represents the document.

class Document : public Node, public NodeContainer
{
public:
	//! Default constructor.
	Document();

	//
	// Properties.
	//

	//! Get the real type of the node.
	virtual NodeType type() const;

	//! Checks if the document has a root element.
	bool hasRootElement() const;

	//
	// Methods.
	//

	//! Get the root element.
	const ElementNodePtr getRootElement() const;

	//! Get the root element.
	ElementNodePtr getRootElement();

private:
	//
	// Members.
	//

	//! Destructor.
	virtual ~Document();
};

//! The default Document smart-pointer type.
typedef Core::RefCntPtr<Document> DocumentPtr;

////////////////////////////////////////////////////////////////////////////////
//! Get the real type of the node.

inline NodeType Document::type() const
{
	return DOCUMENT_NODE;
}

//namespace XML
}

#endif // XML_DOCUMENT_HPP
