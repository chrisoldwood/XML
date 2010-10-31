////////////////////////////////////////////////////////////////////////////////
//! \file   CommentNodeTests.cpp
//! \brief  The unit tests for the CommentNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/CommentNode.hpp>

TEST_SET(CommentNode)
{

TEST_CASE("compilation only succeeds for construction on the heap")
{
//	XML::CommentNode stackNode;		// Shouldn't compile.

	XML::CommentNodePtr heapNode(new XML::CommentNode);

	TEST_PASSED("compilation succeeds");
}
TEST_CASE_END

TEST_CASE("type returns the type of the node as an enumeration value")
{
	XML::CommentNodePtr node(new XML::CommentNode);

	TEST_TRUE(node->type() == XML::COMMENT_NODE);
	TEST_TRUE(tstricmp(node->typeStr(), TXT("comment")) == 0);
}
TEST_CASE_END

TEST_CASE("default construction results in an empty comment value")
{
	XML::CommentNodePtr node(new XML::CommentNode);

	TEST_TRUE(node->comment().empty());
}
TEST_CASE_END

TEST_CASE("the comment value can be set via the constructor")
{
	XML::CommentNodePtr node = XML::CommentNodePtr(new XML::CommentNode(TXT("comment")));

	TEST_TRUE(node->comment() == TXT("comment"));
}
TEST_CASE_END

TEST_CASE("the comment value can be set via a mutator")
{
	XML::CommentNodePtr node = XML::CommentNodePtr(new XML::CommentNode);

	node->setComment(TXT("comment"));

	TEST_TRUE(node->comment() == TXT("comment"));
}
TEST_CASE_END

}
TEST_SET_END
