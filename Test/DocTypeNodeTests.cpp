////////////////////////////////////////////////////////////////////////////////
//! \file   DocTypeNodeTests.cpp
//! \brief  The unit tests for the DocTypeNode class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <XML/DocTypeNode.hpp>

TEST_SET(DocTypeNode)
{

TEST_CASE("compilation only succeeds for construction on the heap")
{
//	XML::DocTypeNode stackNode;		// Shouldn't compile.

	XML::DocTypeNodePtr heapNode(new XML::DocTypeNode);

	TEST_PASSED("compilation succeeds");
}
TEST_CASE_END

TEST_CASE("type returns the type of the node as an enumeration value")
{
	XML::DocTypeNodePtr node(new XML::DocTypeNode);

	TEST_TRUE(node->type() == XML::DOCTYPE_NODE);
	TEST_TRUE(tstricmp(node->typeStr(), TXT("document type")) == 0);
}
TEST_CASE_END

TEST_CASE("default construction results in an empty declaration value")
{
	XML::DocTypeNodePtr node(new XML::DocTypeNode);

	TEST_TRUE(node->declaration().empty());
}
TEST_CASE_END

TEST_CASE("the declaration value can be set via the constructor")
{
	XML::DocTypeNodePtr node = XML::DocTypeNodePtr(new XML::DocTypeNode(TXT("declaration")));

	TEST_TRUE(node->declaration() == TXT("declaration"));
}
TEST_CASE_END

TEST_CASE("the declaration value can be set via a mutator")
{
	XML::DocTypeNodePtr node = XML::DocTypeNodePtr(new XML::DocTypeNode);

	node->setDeclaration(TXT("declaration"));

	TEST_TRUE(node->declaration() == TXT("declaration"));
}
TEST_CASE_END

}
TEST_SET_END
