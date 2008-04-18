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
	TEST_TRUE(pNode->Target().empty());

	pNode = XML::ProcessingNodePtr(new XML::ProcessingNode(TXT("Target1")));

	TEST_TRUE(pNode->Target() == TXT("Target1"));

	pNode->SetTarget(TXT("Target2"));

	TEST_TRUE(pNode->Target() == TXT("Target2"));
}
