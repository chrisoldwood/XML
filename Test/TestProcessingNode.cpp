////////////////////////////////////////////////////////////////////////////////
//! \file   TestProcessingNode.cpp
//! \brief  The unit tests for the ProcessingNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/ProcessingNode.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the ProcessingNode class.

void TestProcessingNode()
{
//	XML::ProcessingNode oNode;		// Shouldn't compile.

	XML::ProcessingNodePtr pNode(new XML::ProcessingNode);

	TEST_TRUE(pNode->Type() == XML::PROCESSING_NODE);
}
