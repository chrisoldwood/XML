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
	: m_strTarget()
	, m_vAttribs()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a target.

ProcessingNode::ProcessingNode(const tstring& strTarget)
	: m_strTarget(strTarget)
	, m_vAttribs()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a target and attributes.

ProcessingNode::ProcessingNode(const tstring& strTarget, const Attributes& vAttribs)
	: m_strTarget(strTarget)
	, m_vAttribs(vAttribs)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

ProcessingNode::~ProcessingNode()
{
}

//namespace XML
}
