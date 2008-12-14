////////////////////////////////////////////////////////////////////////////////
//! \file   Test.cpp
//! \brief  The test harness entry point.
//! \author Chris Oldwood

#include "stdafx.h"
#include <tchar.h>
#include <Core/UnitTest.hpp>

////////////////////////////////////////////////////////////////////////////////
// The test group functions.

extern void TestAttributes();
extern void TestCharTable();
extern void TestTextNode();
extern void TestCommentNode();
extern void TestProcessingNode();
extern void TestElementNode();
extern void TestCDataNode();
extern void TestDocument();
extern void TestReader();
extern void TestWriter();
extern void TestXPathIterator();

////////////////////////////////////////////////////////////////////////////////
//! The entry point for the test harness.

int _tmain(int argc, _TCHAR* argv[])
{
	TEST_SUITE_BEGIN(argc, argv)
	{
		TEST_CASE(TestAttributes);
		TEST_CASE(TestCharTable);
		TEST_CASE(TestTextNode);
		TEST_CASE(TestCommentNode);
		TEST_CASE(TestProcessingNode);
		TEST_CASE(TestElementNode);
		TEST_CASE(TestCDataNode);
		TEST_CASE(TestDocument);
		TEST_CASE(TestReader);
		TEST_CASE(TestWriter);
		TEST_CASE(TestXPathIterator);

		Core::SetTestRunFinalStatus(true);
	}
	TEST_SUITE_END
}
