////////////////////////////////////////////////////////////////////////////////
//! \file   TestCommentNode.cpp
//! \brief  The unit tests for the CommentNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/CommentNode.hpp>

TEST_SET(CommentNode)
{
//	XML::CommentNode oNode;		// Shouldn't compile.

	XML::CommentNodePtr pNode(new XML::CommentNode);

	TEST_TRUE(pNode->type() == XML::COMMENT_NODE);
	TEST_TRUE(tstrlen(pNode->typeStr()) != 0);
	TEST_TRUE(pNode->comment().empty());

	pNode = XML::CommentNodePtr(new XML::CommentNode(TXT("Comment1")));

	TEST_TRUE(pNode->comment() == TXT("Comment1"));

	pNode->setComment(TXT("Comment2"));

	TEST_TRUE(pNode->comment() == TXT("Comment2"));
}
TEST_SET_END
