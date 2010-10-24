////////////////////////////////////////////////////////////////////////////////
//! \file   TestCharTable.cpp
//! \brief  The unit tests for the CharTable class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/CharTable.hpp>

TEST_SET(CharTable)
{
	XML::CharTable oCharTable;

	TEST_TRUE(oCharTable.isWhitespace(TXT('A')) == false);
	TEST_TRUE(oCharTable.isWhitespace(TXT(' ')) == true);
	TEST_TRUE(oCharTable.isWhitespace(TXT('\t')) == true);
	TEST_TRUE(oCharTable.isWhitespace(TXT('\r')) == true);
	TEST_TRUE(oCharTable.isWhitespace(TXT('\n')) == true);

	TEST_TRUE(oCharTable.isIdentifier(TXT(' ')) == false);
	TEST_TRUE(oCharTable.isIdentifier(TXT('M')) == true);
	TEST_TRUE(oCharTable.isIdentifier(TXT('m')) == true);
	TEST_TRUE(oCharTable.isIdentifier(TXT('5')) == true);
	TEST_TRUE(oCharTable.isIdentifier(TXT('-')) == true);
	TEST_TRUE(oCharTable.isIdentifier(TXT('_')) == true);
	TEST_TRUE(oCharTable.isIdentifier(TXT('.')) == true);

	const tchar nonAscii = TXT('\xFF');

	TEST_TRUE(oCharTable.isIdentifier(nonAscii) == false);
}
TEST_SET_END
