////////////////////////////////////////////////////////////////////////////////
//! \file   TestCharTable.cpp
//! \brief  The unit tests for the CharTable class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/CharTable.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the CharTable class.

void TestCharTable()
{
	XML::CharTable oCharTable;

	TEST_TRUE(oCharTable.IsWhitespace(TXT('A')) == false);
	TEST_TRUE(oCharTable.IsWhitespace(TXT(' ')) == true);
	TEST_TRUE(oCharTable.IsWhitespace(TXT('\t')) == true);
	TEST_TRUE(oCharTable.IsWhitespace(TXT('\r')) == true);
	TEST_TRUE(oCharTable.IsWhitespace(TXT('\n')) == true);

	TEST_TRUE(oCharTable.IsIdentifier(TXT(' ')) == false);
	TEST_TRUE(oCharTable.IsIdentifier(TXT('M')) == true);
	TEST_TRUE(oCharTable.IsIdentifier(TXT('m')) == true);
	TEST_TRUE(oCharTable.IsIdentifier(TXT('5')) == true);
	TEST_TRUE(oCharTable.IsIdentifier(TXT('-')) == true);
	TEST_TRUE(oCharTable.IsIdentifier(TXT('_')) == true);
	TEST_TRUE(oCharTable.IsIdentifier(TXT('.')) == true);
}
