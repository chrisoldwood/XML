////////////////////////////////////////////////////////////////////////////////
//! \file   ProcessingNode.cpp
//! \brief  The ProcessingNode class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ProcessingNode.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

ProcessingNode::ProcessingNode()
	: m_target()
	, m_attributes()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a target.

ProcessingNode::ProcessingNode(const tstring& target_)
	: m_target(target_)
	, m_attributes()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a target and attributes.

ProcessingNode::ProcessingNode(const tstring& target_, const Attributes& attributes)
	: m_target(target_)
	, m_attributes(attributes)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ProcessingNode::~ProcessingNode()
{
}

//namespace XML
}
