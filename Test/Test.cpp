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
extern void TestDocument();
extern void TestReader();
extern void TestWriter();

////////////////////////////////////////////////////////////////////////////////
//! The entry point for the test harness.

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	TEST_SUITE_BEGIN
	{
		TestAttributes();
		TestCharTable();
		TestTextNode();
		TestCommentNode();
		TestProcessingNode();
		TestElementNode();
		TestDocument();
		TestReader();
		TestWriter();

		Core::SetTestRunFinalStatus(true);
	}
	TEST_SUITE_END
}
