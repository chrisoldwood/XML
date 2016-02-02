////////////////////////////////////////////////////////////////////////////////
//! \file   CDataNodeTests.cpp
//! \brief  The unit tests for the CDataNode class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <XML/CDataNode.hpp>

TEST_SET(CDataNode)
{

TEST_CASE("compilation only succeeds for construction on the heap")
{
//	XML::CDataNode stackNode;		// Shouldn't compile.

	XML::CDataNodePtr heapNode(new XML::CDataNode);

	TEST_PASSED("compilation succeeds");
}
TEST_CASE_END

TEST_CASE("type returns the type of the node as an enumeration value")
{
	XML::CDataNodePtr node(new XML::CDataNode);

	TEST_TRUE(node->type() == XML::CDATA_NODE);
	TEST_TRUE(tstricmp(node->typeStr(), TXT("cdata")) == 0);
}
TEST_CASE_END

TEST_CASE("default construction results in an empty text value")
{
	XML::CDataNodePtr node(new XML::CDataNode);

	TEST_TRUE(node->text().empty());
}
TEST_CASE_END

TEST_CASE("the text value can be set via the constructor")
{
	XML::CDataNodePtr node = XML::CDataNodePtr(new XML::CDataNode(TXT("text value")));

	TEST_TRUE(node->text() == TXT("text value"));
}
TEST_CASE_END

TEST_CASE("the text value can be set via a mutator")
{
	XML::CDataNodePtr node = XML::CDataNodePtr(new XML::CDataNode);

	node->setText(TXT("text value"));

	TEST_TRUE(node->text() == TXT("text value"));
}
TEST_CASE_END

}
TEST_SET_END
