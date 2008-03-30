////////////////////////////////////////////////////////////////////////////////
//! \file   TestCommentNode.cpp
//! \brief  The unit tests for the CommentNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/CommentNode.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the CommentNode class.

void TestCommentNode()
{
//	XML::CommentNode oNode;		// Shouldn't compile.

	XML::CommentNodePtr pNode(new XML::CommentNode);

	TEST_TRUE(pNode->Type() == XML::COMMENT_NODE);
	TEST_TRUE(pNode->Comment().empty());

	pNode = XML::CommentNodePtr(new XML::CommentNode(TXT("Comment1")));

	TEST_TRUE(pNode->Comment() == TXT("Comment1"));

	pNode->SetComment(TXT("Comment2"));

	TEST_TRUE(pNode->Comment() == TXT("Comment2"));
}
