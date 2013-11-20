////////////////////////////////////////////////////////////////////////////////
//! \file   WriterTests.cpp
//! \brief  The unit tests for the Writer class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/Writer.hpp>

TEST_SET(Writer)
{

TEST_CASE("An empty document is serialized as an empty string")
{
	XML::DocumentPtr emptyDocument(new XML::Document);

	const tstring output = XML::Writer::writeDocument(emptyDocument);

	TEST_TRUE(output == TXT(""));
}
TEST_CASE_END

TEST_CASE("An empty element is serialized as a single tag")
{
	XML::DocumentPtr    document(new XML::Document);
	XML::ElementNodePtr rootNode(new XML::ElementNode(TXT("root")));
	
	document->appendChild(rootNode);

	const tstring output = XML::Writer::writeDocument(document);

	TEST_TRUE(output == TXT("<root/>"));
}
TEST_CASE_END

TEST_CASE("A parent element is serialized as a pair of tags")
{
	XML::DocumentPtr    document(new XML::Document);
	XML::ElementNodePtr parentNode(new XML::ElementNode(TXT("parent")));
	XML::ElementNodePtr childNode(new XML::ElementNode(TXT("child")));
	
	document->appendChild(parentNode);
	parentNode->appendChild(childNode);

	const tstring output = XML::Writer::writeDocument(document);

	TEST_TRUE(output == TXT("<parent><child/></parent>"));
}
TEST_CASE_END

TEST_CASE("Multiple child elements are serialized within the parent tags")
{
	XML::DocumentPtr    document(new XML::Document);
	XML::ElementNodePtr parentNode(new XML::ElementNode(TXT("parent")));
	XML::ElementNodePtr childNode1(new XML::ElementNode(TXT("child1")));
	XML::ElementNodePtr childNode2(new XML::ElementNode(TXT("child2")));
	
	document->appendChild(parentNode);
	parentNode->appendChild(childNode1);
	parentNode->appendChild(childNode2);

	const tstring output = XML::Writer::writeDocument(document);

	TEST_TRUE(output == TXT("<parent><child1/><child2/></parent>"));
}
TEST_CASE_END

TEST_CASE("Attributes on an empty element are serialized as key/value pairs in the tag")
{
	XML::DocumentPtr    document(new XML::Document);
	XML::ElementNodePtr rootNode(new XML::ElementNode(TXT("root")));
	XML::AttributePtr   attribute(new XML::Attribute(TXT("key"), TXT("value")));
	
	document->appendChild(rootNode);
	rootNode->getAttributes().setAttribute(attribute);

	const tstring output = XML::Writer::writeDocument(document);

	TEST_TRUE(output == TXT("<root key=\"value\"/>"));
}
TEST_CASE_END

TEST_CASE("Attributes on an non-empty element are serialized as key/value pairs in the opening tag")
{
	XML::DocumentPtr    document(new XML::Document);
	XML::ElementNodePtr parentNode(new XML::ElementNode(TXT("parent")));
	XML::ElementNodePtr childNode(new XML::ElementNode(TXT("child")));
	XML::AttributePtr   attribute(new XML::Attribute(TXT("key"), TXT("value")));
	
	document->appendChild(parentNode);
	parentNode->appendChild(childNode);
	parentNode->getAttributes().setAttribute(attribute);

	const tstring output = XML::Writer::writeDocument(document);

	TEST_TRUE(output == TXT("<parent key=\"value\"><child/></parent>"));
}
TEST_CASE_END

}
TEST_SET_END
