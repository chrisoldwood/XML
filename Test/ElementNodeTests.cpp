////////////////////////////////////////////////////////////////////////////////
//! \file   ElementNodeTests.cpp
//! \brief  The unit tests for the ElementNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/ElementNode.hpp>

TEST_SET(ElementNode)
{

TEST_CASE("compilation only succeeds for construction on the heap")
{
//	XML::ElementNode stackNode;		// Shouldn't compile.

	XML::ElementNodePtr heapNode(new XML::ElementNode);

	TEST_PASSED("compilation succeeds");
}
TEST_CASE_END

TEST_CASE("type returns the type of the node as an enumeration value")
{
	XML::ElementNodePtr node(new XML::ElementNode);

	TEST_TRUE(node->type() == XML::ELEMENT_NODE);
	TEST_TRUE(tstricmp(node->typeStr(), TXT("element")) == 0);
}
TEST_CASE_END

TEST_CASE("default construction results in an empty name")
{
	XML::ElementNodePtr node(new XML::ElementNode);

	TEST_TRUE(node->name().empty());
}
TEST_CASE_END

TEST_CASE("the name can be set via the constructor")
{
	XML::ElementNodePtr node = XML::ElementNodePtr(new XML::ElementNode(TXT("name")));

	TEST_TRUE(node->name() == TXT("name"));
}
TEST_CASE_END

TEST_CASE("the name can be set via a mutator")
{
	XML::ElementNodePtr node = XML::ElementNodePtr(new XML::ElementNode);

	node->setName(TXT("name"));

	TEST_TRUE(node->name() == TXT("name"));
}
TEST_CASE_END

}
TEST_SET_END
