////////////////////////////////////////////////////////////////////////////////
//! \file   Test.cpp
//! \brief  The test harness entry point.
//! \author Chris Oldwood

#include "stdafx.h"
#include <tchar.h>
#include <Core/UnitTest.hpp>

////////////////////////////////////////////////////////////////////////////////
// The test group functions.

extern void testAttributes();
extern void testCharTable();
extern void testTextNode();
extern void testCommentNode();
extern void testProcessingNode();
extern void testElementNode();
extern void testCDataNode();
extern void testDocument();
extern void testReader();
extern void testWriter();
extern void testXPathIterator();

////////////////////////////////////////////////////////////////////////////////
//! The entry point for the test harness.

int _tmain(int argc, _TCHAR* argv[])
{
	TEST_SUITE_BEGIN(argc, argv)
	{
		TEST_CASE(testAttributes);
		TEST_CASE(testCharTable);
		TEST_CASE(testTextNode);
		TEST_CASE(testCommentNode);
		TEST_CASE(testProcessingNode);
		TEST_CASE(testElementNode);
		TEST_CASE(testCDataNode);
		TEST_CASE(testDocument);
		TEST_CASE(testReader);
		TEST_CASE(testWriter);
		TEST_CASE(testXPathIterator);

		Core::setTestRunFinalStatus(true);
	}
	TEST_SUITE_END
}
