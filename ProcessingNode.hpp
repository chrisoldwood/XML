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
	ProcessingNode(const tstring& target);

	//! Construction from a target and attributes.
	ProcessingNode(const tstring& target, const Attributes& attributes);

	//
	// Properties
	//

	//! Get the real type of the node.
	virtual NodeType type() const;

	//! Get the target.
	const tstring& target() const;

	//! Set the target.
	void setTarget(const tstring& target);

	//! Get the attributes.
	const Attributes& getAttributes() const;

	//! Get the attributes.
	Attributes& getAttributes();

private:
	//
	// Members.
	//
	tstring		m_target;		//!< The target text.
	Attributes	m_attributes;	//!< The attributes.

	//! Destructor.
	virtual ~ProcessingNode();
};

//! The default ProcessingNode smart-pointer type.
typedef Core::RefCntPtr<ProcessingNode> ProcessingNodePtr;

////////////////////////////////////////////////////////////////////////////////
//! Get the real type of the node.

inline NodeType ProcessingNode::type() const
{
	return PROCESSING_NODE;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the target.

inline const tstring& ProcessingNode::target() const
{
	return m_target;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the target.

inline void ProcessingNode::setTarget(const tstring& target_)
{
	m_target = target_;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the attributes.

inline const Attributes& ProcessingNode::getAttributes() const
{
	return m_attributes;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the attributes.

inline Attributes& ProcessingNode::getAttributes()
{
	return m_attributes;
}

//namespace XML
}

#endif // XML_PROCESSINGNODE_HPP
