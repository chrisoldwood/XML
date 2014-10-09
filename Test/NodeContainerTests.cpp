////////////////////////////////////////////////////////////////////////////////
//! \file   NodeContainerTests.cpp
//! \brief  The unit tests for the NodeContainer class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/ElementNode.hpp>
#include <XML/CommentNode.hpp>

TEST_SET(NodeContainer)
{

TEST_CASE("a node container is initially empty")
{
	XML::ElementNodePtr container = XML::makeElement();

	TEST_FALSE(container->hasChildren());
	TEST_TRUE(container->getChildCount() == 0);
}
TEST_CASE_END

TEST_CASE("after adding a child node the container is not empty")
{
	XML::ElementNodePtr container = XML::makeElement();
	XML::ElementNodePtr child = XML::makeElement(TXT("child"));

	container->appendChild(child);

	TEST_TRUE(container->hasChildren());
	TEST_TRUE(container->getChildCount() == 1);
}
TEST_CASE_END

TEST_CASE("a child can be retrieved by its index")
{
	XML::ElementNodePtr container = XML::makeElement();
	XML::ElementNodePtr child = XML::makeElement(TXT("child"));

	container->appendChild(child);

	TEST_TRUE(container->getChild(0) == child);
}
TEST_CASE_END

TEST_CASE("a child can be retrieved by its index and downcast to its concrete node type")
{
	XML::ElementNodePtr container = XML::makeElement();
	XML::ElementNodePtr child = XML::makeElement(TXT("child"));

	container->appendChild(child);

	TEST_TRUE(container->getChild<XML::ElementNode>(0)->name() == TXT("child"));
}
TEST_CASE_END

TEST_CASE("retrieving a child node and downcasting to the wrong type throws")
{
	XML::ElementNodePtr container = XML::makeElement();
	XML::ElementNodePtr child = XML::makeElement(TXT("child"));

	container->appendChild(child);

	TEST_THROWS(container->getChild<XML::CommentNode>(0));
}
TEST_CASE_END

TEST_CASE("attempting to retrieve a child by an invalid index throws an exception")
{
	XML::ElementNodePtr container = XML::makeElement();

	TEST_THROWS(container->getChild(0));
}
TEST_CASE_END

TEST_CASE("child nodes maintain the order they are added")
{
	XML::ElementNodePtr container = XML::makeElement();
	XML::ElementNodePtr first = XML::makeElement(TXT("first"));
	XML::ElementNodePtr second = XML::makeElement(TXT("second"));

	container->appendChild(first);
	container->appendChild(second);

	TEST_TRUE(container->getChild(0) == first);
	TEST_TRUE(container->getChild(1) == second);
}
TEST_CASE_END

TEST_CASE("the child nodes can be iterated in the order they were added")
{
	XML::ElementNodePtr container = XML::makeElement();
	XML::ElementNodePtr first = XML::makeElement(TXT("first"));
	XML::ElementNodePtr second = XML::makeElement(TXT("second"));

	container->appendChild(first);
	container->appendChild(second);

	XML::NodeContainer::iterator it = container->beginChild();
	XML::NodeContainer::iterator end = container->endChild();

	TEST_TRUE(*it++ == first);
	TEST_TRUE(*it++ == second);
	TEST_TRUE(it == end);
}
TEST_CASE_END

TEST_CASE("iterating the children of a const node requires a const iterator")
{
	XML::ElementNodePtr container = XML::makeElement();
	XML::ElementNodePtr first = XML::makeElement(TXT("first"));
	XML::ElementNodePtr second = XML::makeElement(TXT("second"));

	container->appendChild(first);
	container->appendChild(second);

	const XML::ElementNodePtr constContainer = container;

	XML::NodeContainer::const_iterator it = constContainer->beginChild();
	XML::NodeContainer::const_iterator end = constContainer->endChild();

	TEST_TRUE(*it++ == first);
	TEST_TRUE(*it++ == second);
	TEST_TRUE(it == end);
}
TEST_CASE_END

}
TEST_SET_END
