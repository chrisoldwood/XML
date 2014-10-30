////////////////////////////////////////////////////////////////////////////////
//! \file   WriterTests.cpp
//! \brief  The unit tests for the Writer class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/Writer.hpp>
#include <XML/TextNode.hpp>

TEST_SET(Writer)
{
	const uint defaultTestFlags = XML::Writer::NO_FORMATTING;

TEST_CASE("An empty document is serialized as an empty string")
{
	XML::DocumentPtr emptyDocument(new XML::Document);

	const tstring output = XML::Writer::writeDocument(emptyDocument, defaultTestFlags);

	TEST_TRUE(output == TXT(""));
}
TEST_CASE_END

TEST_CASE("An empty element is serialized as a single tag")
{
	XML::DocumentPtr    document(new XML::Document);
	XML::ElementNodePtr rootNode(new XML::ElementNode(TXT("root")));
	
	document->appendChild(rootNode);

	const tstring output = XML::Writer::writeDocument(document, defaultTestFlags);

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

	const tstring output = XML::Writer::writeDocument(document, defaultTestFlags);

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

	const tstring output = XML::Writer::writeDocument(document, defaultTestFlags);

	TEST_TRUE(output == TXT("<parent><child1/><child2/></parent>"));
}
TEST_CASE_END

TEST_CASE("Attributes on an empty element are serialized as key/value pairs in the tag")
{
	XML::DocumentPtr    document(new XML::Document);
	XML::ElementNodePtr rootNode(new XML::ElementNode(TXT("root")));
	XML::AttributePtr   attribute(new XML::Attribute(TXT("key"), TXT("value")));
	
	document->appendChild(rootNode);
	rootNode->getAttributes().set(attribute);

	const tstring output = XML::Writer::writeDocument(document, defaultTestFlags);

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
	parentNode->getAttributes().set(attribute);

	const tstring output = XML::Writer::writeDocument(document, defaultTestFlags);

	TEST_TRUE(output == TXT("<parent key=\"value\"><child/></parent>"));
}
TEST_CASE_END

TEST_CASE("elements are written one per line and indented using a tab character by default")
{
	XML::DocumentPtr    document(new XML::Document);
	XML::ElementNodePtr grandparentNode(new XML::ElementNode(TXT("grandparent")));
	XML::ElementNodePtr parentNode(new XML::ElementNode(TXT("parent")));
	XML::ElementNodePtr childNode(new XML::ElementNode(TXT("child")));
	
	document->appendChild(grandparentNode);
	grandparentNode->appendChild(parentNode);
	parentNode->appendChild(childNode);

	const tstring output = XML::Writer::writeDocument(document);

	TEST_TRUE(output == TXT("<grandparent>\n\t<parent>\n\t\t<child/>\n\t</parent>\n</grandparent>\n"));
}
TEST_CASE_END

TEST_CASE("The indenting style can be overridden")
{
	XML::DocumentPtr    document(new XML::Document);
	XML::ElementNodePtr grandparentNode(new XML::ElementNode(TXT("grandparent")));
	XML::ElementNodePtr parentNode(new XML::ElementNode(TXT("parent")));
	XML::ElementNodePtr childNode(new XML::ElementNode(TXT("child")));
	
	document->appendChild(grandparentNode);
	grandparentNode->appendChild(parentNode);
	parentNode->appendChild(childNode);

	const tstring output = XML::Writer::writeDocument(document, XML::Writer::DEFAULT, TXT("  "));

	TEST_TRUE(output == TXT("<grandparent>\n  <parent>\n    <child/>\n  </parent>\n</grandparent>\n"));
}
TEST_CASE_END

TEST_CASE("A child text node is written between the element tags when no formatting is specified")
{
	XML::DocumentPtr document = XML::makeDocument
	(
		XML::makeElement
		(
			TXT("root"), XML::makeElement
			(
				TXT("element"), XML::makeText(TXT("value"))
			)
		)
	);
	
	const tstring output = XML::Writer::writeDocument(document, defaultTestFlags);

	TEST_TRUE(output == TXT("<root><element>value</element></root>"));
}
TEST_CASE_END

TEST_CASE("A single child text node and the element tags are written on the same line")
{
	XML::DocumentPtr document = XML::makeDocument
	(
		XML::makeElement
		(
			TXT("root"), XML::makeElement
			(
				TXT("element"), XML::makeText(TXT("value"))
			)
		)
	);
	
	const tstring output = XML::Writer::writeDocument(document, XML::Writer::DEFAULT, TXT("  "));

	TEST_TRUE(output == TXT("<root>\n  <element>value</element>\n</root>\n"));
}
TEST_CASE_END

}
TEST_SET_END
