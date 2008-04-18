////////////////////////////////////////////////////////////////////////////////
//! \file   TestDocTypeNode.cpp
//! \brief  The unit tests for the DocTypeNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/DocTypeNode.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the DocTypeNode class.

void TestDocTypeNode()
{
//	XML::DocTypeNode oNode;		// Shouldn't compile.

	XML::DocTypeNodePtr pNode(new XML::DocTypeNode);

	TEST_TRUE(pNode->Type() == XML::DOCTYPE_NODE);
	TEST_TRUE(pNode->Declaration().empty());

	pNode = XML::DocTypeNodePtr(new XML::DocTypeNode(TXT("Declaration1")));

	TEST_TRUE(pNode->Declaration() == TXT("Declaration1"));

	pNode->SetDeclaration(TXT("Declaration2"));

	TEST_TRUE(pNode->Declaration() == TXT("Declaration2"));
}
