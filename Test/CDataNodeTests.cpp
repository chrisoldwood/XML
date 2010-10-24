////////////////////////////////////////////////////////////////////////////////
//! \file   TestCDataNode.cpp
//! \brief  The unit tests for the CDataNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/CDataNode.hpp>

TEST_SET(CDataNode)
{
//	XML::CDataNode oNode;		// Shouldn't compile.

	XML::CDataNodePtr pNode(new XML::CDataNode);

	TEST_TRUE(pNode->type() == XML::CDATA_NODE);
	TEST_TRUE(tstrlen(pNode->typeStr()) != 0);
	TEST_TRUE(pNode->text().empty());

	pNode = XML::CDataNodePtr(new XML::CDataNode(TXT("CData1")));

	TEST_TRUE(pNode->text() == TXT("CData1"));

	pNode->setText(TXT("CData2"));

	TEST_TRUE(pNode->text() == TXT("CData2"));
}
TEST_SET_END
