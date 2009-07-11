////////////////////////////////////////////////////////////////////////////////
//! \file   DocTypeNode.hpp
//! \brief  The DocTypeNode class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_DOCTYPENODE_HPP
#define XML_DOCTYPENODE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Node.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The XML node type used for the document type. The document type details are
//! stored as a single string and not parsed.

class DocTypeNode : public Node
{
public:
	//! Default constructor.
	DocTypeNode();

	//! Construction from a string declaration.
	DocTypeNode(const tstring& strDeclaration);

	//
	// Properties
	//

	//! Get the real type of the node.
	virtual NodeType type() const;

	//! Get the declaration.
	const tstring& declaration() const;

	//! Set the declaration.
	void setDeclaration(const tstring& strDeclaration);

private:
	//
	// Members.
	//
	tstring	m_strDeclaration;		//!< The string declaration.

	//! Destructor.
	virtual ~DocTypeNode();
};

//! The default DocType smart-pointer type.
typedef Core::RefCntPtr<DocTypeNode> DocTypeNodePtr;

////////////////////////////////////////////////////////////////////////////////
//! Get the real type of the node.

inline NodeType DocTypeNode::type() const
{
	return DOCTYPE_NODE;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the declaration.

inline const tstring& DocTypeNode::declaration() const
{
	return m_strDeclaration;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the declaration.

inline void DocTypeNode::setDeclaration(const tstring& strDeclaration)
{
	m_strDeclaration = strDeclaration;
}

//namespace XML
}

#endif // XML_DOCTYPENODE_HPP
