////////////////////////////////////////////////////////////////////////////////
//! \file   TestTextNode.cpp
//! \brief  The unit tests for the TextNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/TextNode.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the TextNode class.

void testTextNode()
{
//	XML::TextNode oNode;		// Shouldn't compile.

	XML::TextNodePtr pNode(new XML::TextNode);

	TEST_TRUE(pNode->type() == XML::TEXT_NODE);
	TEST_TRUE(pNode->text().empty());

	pNode = XML::TextNodePtr(new XML::TextNode(TXT("Text1")));

	TEST_TRUE(pNode->text() == TXT("Text1"));

	pNode->setText(TXT("Text2"));

	TEST_TRUE(pNode->text() == TXT("Text2"));
}
