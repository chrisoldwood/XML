////////////////////////////////////////////////////////////////////////////////
//! \file   TestCDataNode.cpp
//! \brief  The unit tests for the CDataNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/CDataNode.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the CDataNode class.

void TestCDataNode()
{
//	XML::CDataNode oNode;		// Shouldn't compile.

	XML::CDataNodePtr pNode(new XML::CDataNode);

	TEST_TRUE(pNode->Type() == XML::CDATA_NODE);
	TEST_TRUE(pNode->Text().empty());

	pNode = XML::CDataNodePtr(new XML::CDataNode(TXT("CData1")));

	TEST_TRUE(pNode->Text() == TXT("CData1"));

	pNode->SetText(TXT("CData2"));

	TEST_TRUE(pNode->Text() == TXT("CData2"));
}
