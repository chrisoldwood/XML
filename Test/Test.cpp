////////////////////////////////////////////////////////////////////////////////
//! \file   Test.cpp
//! \brief  The test harness entry point.
//! \author Chris Oldwood

#include "stdafx.h"
#include <tchar.h>
#include <Core/UnitTest.hpp>

////////////////////////////////////////////////////////////////////////////////
// The test group functions.

extern void TestTextNode();
extern void TestCommentNode();
extern void TestProcessingNode();
extern void TestElementNode();
extern void TestDocument();

////////////////////////////////////////////////////////////////////////////////
//! The entry point for the test harness.

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	TEST_SUITE_BEGIN
	{
		TestTextNode();
		TestCommentNode();
		TestProcessingNode();
		TestElementNode();
		TestDocument();

		Core::SetTestRunFinalStatus(true);
	}
	TEST_SUITE_END
}
