////////////////////////////////////////////////////////////////////////////////
//! \file   ElementNodeTests.cpp
//! \brief  The unit tests for the ElementNode class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <XML/ElementNode.hpp>
#include <XML/TextNode.hpp>

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

	attributes.set(attribute);

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

TEST_CASE("the value for a single attribute can be set directly")
{
	XML::ElementNodePtr node = XML::ElementNodePtr(new XML::ElementNode(TXT("element")));

	node->setAttribute(TXT("name"), TXT("value"));

	TEST_TRUE(node->getAttributeValue(TXT("name")) == TXT("value"));
}
TEST_CASE_END

TEST_CASE("the value for a single attribute can be requested by its name")
{
	XML::Attributes attributes;

	XML::AttributePtr attribute = XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value")));

	attributes.set(attribute);

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

TEST_CASE("an element can be constructed with a name and set of attributes via a helper")
{
	XML::AttributePtr   attribute = XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value")));
	XML::Attributes     attributes(attribute);
	XML::ElementNodePtr node = XML::makeElement(TXT("element"), attributes);

	TEST_TRUE(node->name() == TXT("element"));
	TEST_TRUE(node->getAttributes().count() == 1);
	TEST_TRUE(node->getAttributeValue(TXT("name")) == TXT("value"));
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

TEST_CASE("an element can be constructed with a name and a text node via a helper")
{
	XML::ElementNodePtr parent = XML::makeElement(TXT("parent"), XML::makeText(TXT("text")));

	TEST_TRUE(parent->name() == TXT("parent"));
	TEST_TRUE(parent->getChildCount() == 1);

	XML::TextNodePtr firstChild = Core::dynamic_ptr_cast<XML::TextNode>(*parent->beginChild());

	TEST_TRUE(firstChild->text() == TXT("text"));
}
TEST_CASE_END

TEST_CASE("an element can be constructed with a range of nodes")
{
	XML::NodePtr children[] = { XML::makeElement(TXT("child-1")), XML::makeText(TXT("child-2")) };

	XML::ElementNodePtr parent = XML::makeElement(TXT("parent"), children, children+ARRAY_SIZE(children));

	TEST_TRUE(parent->getChildCount() == 2);
	TEST_TRUE(parent->getChild(0)->type() == XML::ELEMENT_NODE);
	TEST_TRUE(parent->getChild(1)->type() == XML::TEXT_NODE);
}
TEST_CASE_END

TEST_CASE("an empty string is returned for the child text when an element has no children")
{
	XML::ElementNodePtr node = XML::makeElement(TXT("element"));

	TEST_TRUE(node->getTextValue() == TXT(""));
}
TEST_CASE_END

TEST_CASE("the child text node for an element can be retrieved directly")
{
	XML::ElementNodePtr node = XML::makeElement(TXT("element"), XML::makeText(TXT("text")));

	TEST_TRUE(node->getTextValue() == TXT("text"));
}
TEST_CASE_END

TEST_CASE("retrieving the child text for an element throws when the child is not a text node")
{
	XML::ElementNodePtr node = XML::makeElement(TXT("element"), XML::makeElement(TXT("child")));

	TEST_THROWS(node->getTextValue());
}
TEST_CASE_END

TEST_CASE("retrieving the child text for an element throws when more than one child exists")
{
	XML::ElementNodePtr parent = XML::makeElement(TXT("parent"));

	parent->appendChild(XML::makeText(TXT("child-1")));
	parent->appendChild(XML::makeText(TXT("child-2")));

	TEST_THROWS(parent->getTextValue());
}
TEST_CASE_END

TEST_CASE("retrieving the first element node returns nothing when none exist")
{
	XML::ElementNodePtr parent = XML::makeElement(TXT("parent"));

	XML::ElementNodePtr child = parent->findFirstElement(TXT("child"));

	TEST_TRUE(child.empty());
}
TEST_CASE_END

TEST_CASE("retrieving the first element node returns only the first node")
{
	XML::NodePtr first = XML::makeElement(TXT("first"));
	XML::NodePtr second = XML::makeElement(TXT("second"));

	XML::NodePtr children[] = { first, second };

	XML::ElementNodePtr parent = XML::makeElement(TXT("parent"), children, children+ARRAY_SIZE(children));

	XML::ElementNodePtr child = parent->findFirstElement(TXT("second"));

	TEST_TRUE(child.get() == second.get());
}
TEST_CASE_END

TEST_CASE("retrieving the first element node returns the first element node")
{
	XML::NodePtr first = XML::makeText(TXT("text"));
	XML::NodePtr second = XML::makeElement(TXT("element"));

	XML::NodePtr children[] = { first, second };

	XML::ElementNodePtr parent = XML::makeElement(TXT("parent"), children, children+ARRAY_SIZE(children));

	XML::ElementNodePtr child = parent->findFirstElement(TXT("element"));

	TEST_TRUE(child.get() == second.get());
}
TEST_CASE_END

}
TEST_SET_END
