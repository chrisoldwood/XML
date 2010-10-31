////////////////////////////////////////////////////////////////////////////////
//! \file   TextNodeTests.cpp
//! \brief  The unit tests for the TextNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/TextNode.hpp>

TEST_SET(TextNode)
{

TEST_CASE("compilation only succeeds for construction on the heap")
{
//	XML::TextNode stackNode;		// Shouldn't compile.

	XML::TextNodePtr heapNode(new XML::TextNode);

	TEST_PASSED("compilation succeeds");
}
TEST_CASE_END

TEST_CASE("type returns the type of the node as an enumeration value")
{
	XML::TextNodePtr node(new XML::TextNode);

	TEST_TRUE(node->type() == XML::TEXT_NODE);
	TEST_TRUE(tstricmp(node->typeStr(), TXT("text")) == 0);
}
TEST_CASE_END

TEST_CASE("default construction results in an empty text value")
{
	XML::TextNodePtr node(new XML::TextNode);

	TEST_TRUE(node->text().empty());
}
TEST_CASE_END

TEST_CASE("the text value can be set via the constructor")
{
	XML::TextNodePtr node = XML::TextNodePtr(new XML::TextNode(TXT("text")));

	TEST_TRUE(node->text() == TXT("text"));
}
TEST_CASE_END

TEST_CASE("the text value can be set via a mutator")
{
	XML::TextNodePtr node = XML::TextNodePtr(new XML::TextNode);

	node->setText(TXT("text"));

	TEST_TRUE(node->text() == TXT("text"));
}
TEST_CASE_END

}
TEST_SET_END
