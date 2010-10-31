////////////////////////////////////////////////////////////////////////////////
//! \file   ProcessingNodeTests.cpp
//! \brief  The unit tests for the ProcessingNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/ProcessingNode.hpp>

TEST_SET(ProcessingNode)
{

TEST_CASE("compilation only succeeds for construction on the heap")
{
//	XML::ProcessingNode stackNode;		// Shouldn't compile.

	XML::ProcessingNodePtr heapNode(new XML::ProcessingNode);

	TEST_PASSED("compilation succeeds");
}
TEST_CASE_END

TEST_CASE("type returns the type of the node as an enumeration value")
{
	XML::ProcessingNodePtr node(new XML::ProcessingNode);

	TEST_TRUE(node->type() == XML::PROCESSING_NODE);
	TEST_TRUE(tstricmp(node->typeStr(), TXT("processing instruction")) == 0);
}
TEST_CASE_END

TEST_CASE("default construction results in an empty target value")
{
	XML::ProcessingNodePtr node(new XML::ProcessingNode);

	TEST_TRUE(node->target().empty());
}
TEST_CASE_END

TEST_CASE("the target value can be set via the constructor")
{
	XML::ProcessingNodePtr node = XML::ProcessingNodePtr(new XML::ProcessingNode(TXT("target")));

	TEST_TRUE(node->target() == TXT("target"));
}
TEST_CASE_END

TEST_CASE("the target value can be set via a mutator")
{
	XML::ProcessingNodePtr node = XML::ProcessingNodePtr(new XML::ProcessingNode);

	node->setTarget(TXT("target"));

	TEST_TRUE(node->target() == TXT("target"));
}
TEST_CASE_END

}
TEST_SET_END
