////////////////////////////////////////////////////////////////////////////////
//! \file   CDataNode.hpp
//! \brief  The CDataNode class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_CDATANODE_HPP
#define XML_CDATANODE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Node.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The XML node type used to for a CDATA section.

class CDataNode : public Node
{
public:
	//! Default constructor.
	CDataNode();

	//! Construction from the text string.
	CDataNode(const tstring& strText);
	
	//
	// Properties
	//

	//! Get the real type of the node.
	virtual NodeType type() const;

	//! Get the text string.
	const tstring& text() const;

	//! Set the text string.
	void setText(const tstring& strText);

private:
	//
	// Members.
	//
	tstring	m_strText;		//!< The text string.

	//! Destructor.
	virtual ~CDataNode();
};

//! The default CDataNode smart-pointer type.
typedef Core::RefCntPtr<CDataNode> CDataNodePtr;

////////////////////////////////////////////////////////////////////////////////
//! Get the real type of the node.

inline NodeType CDataNode::type() const
{
	return CDATA_NODE;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the text string.

inline const tstring& CDataNode::text() const
{
	return m_strText;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the text string.

inline void CDataNode::setText(const tstring& strText)
{
	m_strText = strText;
}

//namespace XML
}

#endif // XML_CDATANODE_HPP
