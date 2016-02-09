////////////////////////////////////////////////////////////////////////////////
//! \file   CharTableTests.cpp
//! \brief  The unit tests for the CharTable class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <XML/CharTable.hpp>

TEST_SET(CharTable)
{

TEST_CASE("table returns true for characters classified as white-space")
{
	XML::CharTable table;

	TEST_TRUE(table.isWhitespace(TXT(' ')) == true);
	TEST_TRUE(table.isWhitespace(TXT('\t')) == true);
	TEST_TRUE(table.isWhitespace(TXT('\r')) == true);
	TEST_TRUE(table.isWhitespace(TXT('\n')) == true);
}
TEST_CASE_END

TEST_CASE("table returns false for characters not classified as white-space")
{
	XML::CharTable table;

	TEST_TRUE(table.isWhitespace(TXT('A')) == false);
}
TEST_CASE_END

TEST_CASE("table returns true for characters that can be used in identifiers")
{
	XML::CharTable table;

	TEST_TRUE(table.isIdentifier(TXT('M')) == true);
	TEST_TRUE(table.isIdentifier(TXT('m')) == true);
	TEST_TRUE(table.isIdentifier(TXT('5')) == true);
	TEST_TRUE(table.isIdentifier(TXT('-')) == true);
	TEST_TRUE(table.isIdentifier(TXT('_')) == true);
	TEST_TRUE(table.isIdentifier(TXT('.')) == true);
}
TEST_CASE_END

TEST_CASE("table returns false for characters that cannot be used in identifiers")
{
	XML::CharTable table;

	TEST_TRUE(table.isIdentifier(TXT(' ')) == false);

	const tchar nonAscii = TXT('\xFF');

	TEST_TRUE(table.isIdentifier(nonAscii) == false);
}
TEST_CASE_END

}
TEST_SET_END
