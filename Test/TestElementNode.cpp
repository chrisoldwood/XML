////////////////////////////////////////////////////////////////////////////////
//! \file   TestElementNode.cpp
//! \brief  The unit tests for the ElementNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/ElementNode.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the ElementNode class.

void TestElementNode()
{
//	XML::ElementNode oNode;		// Shouldn't compile.

	XML::ElementNodePtr pNode(new XML::ElementNode);

	TEST_TRUE(pNode->Type() == XML::ELEMENT_NODE);
	TEST_TRUE(pNode->Name().empty());

	pNode = XML::ElementNodePtr(new XML::ElementNode(TXT("Name1")));

	TEST_TRUE(pNode->Name() == TXT("Name1"));

	pNode->SetName(TXT("Name2"));

	TEST_TRUE(pNode->Name() == TXT("Name2"));
}
