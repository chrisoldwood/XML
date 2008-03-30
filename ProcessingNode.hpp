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

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The XML node type used for a processing instruction.

class ProcessingNode : public Node
{
public:
	//! Default constructor.
	ProcessingNode();

	//
	// Properties
	//

	//! Get the real type of the node.
	virtual NodeType Type() const;

private:
	//
	// Members.
	//

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

//namespace XML
}

#endif // XML_PROCESSINGNODE_HPP
