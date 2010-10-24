////////////////////////////////////////////////////////////////////////////////
//! \file   TestDocTypeNode.cpp
//! \brief  The unit tests for the DocTypeNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/DocTypeNode.hpp>

TEST_SET(DocTypeNode)
{
//	XML::DocTypeNode oNode;		// Shouldn't compile.

	XML::DocTypeNodePtr pNode(new XML::DocTypeNode);

	TEST_TRUE(pNode->type() == XML::DOCTYPE_NODE);
	TEST_TRUE(tstrlen(pNode->typeStr()) != 0);
	TEST_TRUE(pNode->declaration().empty());

	pNode = XML::DocTypeNodePtr(new XML::DocTypeNode(TXT("Declaration1")));

	TEST_TRUE(pNode->declaration() == TXT("Declaration1"));

	pNode->setDeclaration(TXT("Declaration2"));

	TEST_TRUE(pNode->declaration() == TXT("Declaration2"));
}
TEST_SET_END
