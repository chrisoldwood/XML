////////////////////////////////////////////////////////////////////////////////
//! \file   ProcessingNode.hpp
//! \brief  The ProcessingNode class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_PROCESSINGNODE_HPP
#define XML_PROCESSINGNODE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Node.hpp"
#include "Attributes.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The XML node type used for a processing instruction.

class ProcessingNode : public Node
{
public:
	//! Default constructor.
	ProcessingNode();

	//! Construction from a target.
	ProcessingNode(const tstring& strTarget);

	//! Construction from a target and attributes.
	ProcessingNode(const tstring& strTarget, const Attributes& vAttribs);

	//
	// Properties
	//

	//! Get the real type of the node.
	virtual NodeType Type() const;

	//! Get the target.
	const tstring& Target() const;

	//! Set the target.
	void SetTarget(const tstring& strTarget);

	//! Get the attributes.
	const Attributes& GetAttributes() const;

	//! Get the attributes.
	Attributes& GetAttributes();

private:
	//
	// Members.
	//
	tstring		m_strTarget;	//!< The target text.
	Attributes	m_vAttribs;		//!< The attributes.

	//! Destructor.
	virtual ~ProcessingNode();
};

//! The default ProcessingNode smart-pointer type.
typedef Core::RefCntPtr<ProcessingNode> ProcessingNodePtr;

////////////////////////////////////////////////////////////////////////////////
//! Get the real type of the node.

inline NodeType ProcessingNode::Type() const
{
	return PROCESSING_NODE;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the target.

inline const tstring& ProcessingNode::Target() const
{
	return m_strTarget;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the target.

inline void ProcessingNode::SetTarget(const tstring& strTarget)
{
	m_strTarget = strTarget;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the attributes.

inline const Attributes& ProcessingNode::GetAttributes() const
{
	return m_vAttribs;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the attributes.

inline Attributes& ProcessingNode::GetAttributes()
{
	return m_vAttribs;
}

//namespace XML
}

#endif // XML_PROCESSINGNODE_HPP
