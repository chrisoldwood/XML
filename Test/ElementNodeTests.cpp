////////////////////////////////////////////////////////////////////////////////
//! \file   ElementNodeTests.cpp
//! \brief  The unit tests for the ElementNode class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/ElementNode.hpp>

TEST_SET(ElementNode)
{

TEST_CASE("compilation only succeeds for construction on the heap")
{
//	XML::ElementNode stackNode;		// Shouldn't compile.

	XML::ElementNodePtr heapNode(new XML::ElementNode);

	TEST_PASSED("compilation succeeds");
}
TEST_CASE_END

TEST_CASE("type returns the type of the node as an enumeration value")
{
	XML::ElementNodePtr node(new XML::ElementNode);

	TEST_TRUE(node->type() == XML::ELEMENT_NODE);
	TEST_TRUE(tstricmp(node->typeStr(), TXT("element")) == 0);
}
TEST_CASE_END

TEST_CASE("default construction results in an empty name")
{
	XML::ElementNodePtr node(new XML::ElementNode);

	TEST_TRUE(node->name().empty());
}
TEST_CASE_END

TEST_CASE("the name can be set via the constructor")
{
	XML::ElementNodePtr node = XML::ElementNodePtr(new XML::ElementNode(TXT("name")));

	TEST_TRUE(node->name() == TXT("name"));
}
TEST_CASE_END

TEST_CASE("the name can be set via a mutator")
{
	XML::ElementNodePtr node = XML::ElementNodePtr(new XML::ElementNode);

	node->setName(TXT("name"));

	TEST_TRUE(node->name() == TXT("name"));
}
TEST_CASE_END

TEST_CASE("an element can be constructed with a single attribute")
{
	XML::AttributePtr   attribute = XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value")));
	XML::ElementNodePtr node = XML::ElementNodePtr(new XML::ElementNode(TXT("element"), attribute));

	TEST_TRUE(node->name() == TXT("element"));
	TEST_TRUE(node->getAttributes().count() == 1);
	TEST_TRUE(node->getAttributes().get(TXT("name")) == attribute);
}
TEST_CASE_END

TEST_CASE("an element can be constructed with an empty set of attributes")
{
	XML::Attributes     attributes;
	XML::ElementNodePtr node = XML::ElementNodePtr(new XML::ElementNode(TXT("element"), attributes));

	TEST_TRUE(node->name() == TXT("element"));
	TEST_TRUE(node->getAttributes().count() == 0);
}
TEST_CASE_END

TEST_CASE("an element can be constructed with a set of attributes")
{
	XML::Attributes attributes;

	XML::AttributePtr attribute = XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value")));

	attributes.setAttribute(attribute);

	XML::ElementNodePtr node = XML::ElementNodePtr(new XML::ElementNode(TXT("element"), attributes));

	TEST_TRUE(node->name() == TXT("element"));
	TEST_TRUE(node->getAttributes().count() == 1);
	TEST_TRUE(node->getAttributes().get(TXT("name")) == attribute);
}
TEST_CASE_END

TEST_CASE("an element can be constructed with a name and a single child element")
{
	XML::ElementNodePtr child = XML::ElementNodePtr(new XML::ElementNode(TXT("child")));
	XML::ElementNodePtr parent = XML::ElementNodePtr(new XML::ElementNode(TXT("parent"), child));

	TEST_TRUE(parent->name() == TXT("parent"));
	TEST_TRUE(parent->getChildCount() == 1);

	XML::ElementNodePtr firstChild = Core::dynamic_ptr_cast<XML::ElementNode>(*parent->beginChild());

	TEST_TRUE(firstChild->name() == TXT("child"));
}
TEST_CASE_END

TEST_CASE("the value for a single attribute can be requested by its name")
{
	XML::Attributes attributes;

	XML::AttributePtr attribute = XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value")));

	attributes.setAttribute(attribute);

	XML::ElementNodePtr node = XML::ElementNodePtr(new XML::ElementNode(TXT("element"), attributes));

	TEST_TRUE(node->getAttributeValue(TXT("name")) == TXT("value"));
}
TEST_CASE_END

TEST_CASE("requesting the value for an unknown attribute throws")
{
	XML::ElementNodePtr node = XML::ElementNodePtr(new XML::ElementNode(TXT("element")));

	TEST_THROWS(node->getAttributeValue(TXT("unknown")));
}
TEST_CASE_END

TEST_CASE("an element with no name can be constructed via a helper")
{
	XML::ElementNodePtr node = XML::makeElement();

	TEST_TRUE(node->name().empty());
}
TEST_CASE_END

TEST_CASE("an element can be constructed with a name via a helper")
{
	XML::ElementNodePtr node = XML::makeElement(TXT("name"));

	TEST_TRUE(node->name() == TXT("name"));
}
TEST_CASE_END

TEST_CASE("an element can be constructed with a name and single attribute via a helper")
{
	XML::AttributePtr   attribute = XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value")));
	XML::ElementNodePtr node = XML::makeElement(TXT("element"), attribute);

	TEST_TRUE(node->name() == TXT("element"));
	TEST_TRUE(node->getAttributes().count() == 1);
	TEST_TRUE(node->getAttributes().get(TXT("name")) == attribute);
}
TEST_CASE_END

TEST_CASE("an element can be constructed with a name and a single child element via a helper")
{
	XML::ElementNodePtr parent = XML::makeElement(TXT("parent"), XML::makeElement(TXT("child")));

	TEST_TRUE(parent->name() == TXT("parent"));
	TEST_TRUE(parent->getChildCount() == 1);

	XML::ElementNodePtr firstChild = Core::dynamic_ptr_cast<XML::ElementNode>(*parent->beginChild());

	TEST_TRUE(firstChild->name() == TXT("child"));
}
TEST_CASE_END

}
TEST_SET_END
