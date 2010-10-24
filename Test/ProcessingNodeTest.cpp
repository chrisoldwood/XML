////////////////////////////////////////////////////////////////////////////////
//! \file   TestProcessingNode.cpp
//! \brief  The unit tests for the ProcessingNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/ProcessingNode.hpp>

TEST_SET(ProcessingNode)
{
//	XML::ProcessingNode oNode;		// Shouldn't compile.

	XML::ProcessingNodePtr pNode(new XML::ProcessingNode);

	TEST_TRUE(pNode->type() == XML::PROCESSING_NODE);
	TEST_TRUE(tstrlen(pNode->typeStr()) != 0);
	TEST_TRUE(pNode->target().empty());

	pNode = XML::ProcessingNodePtr(new XML::ProcessingNode(TXT("Target1")));

	TEST_TRUE(pNode->target() == TXT("Target1"));

	pNode->setTarget(TXT("Target2"));

	TEST_TRUE(pNode->target() == TXT("Target2"));
}
TEST_SET_END
