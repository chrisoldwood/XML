////////////////////////////////////////////////////////////////////////////////
//! \file   XPathIteratorTests.cpp
//! \brief  The unit tests for the XPathIterator class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <XML/XPathIterator.hpp>
#include <XML/Reader.hpp>

static const tstring s_xml =	TXT("<?xml version='1.0' ?>")
								TXT("<A ID='1'>")
								TXT("    <B ID='2.1'/>")
								TXT("    <C ID='2.2'>")
								TXT("        <B ID='3'/>")
								TXT("    </C>")
								TXT("    <B ID='2.3'/>")
								TXT("</A>");

XML::DocumentPtr s_document;

TEST_SET(XPathIterator)
{

TEST_CASE_SETUP()
{
	s_document = XML::Reader::readDocument(s_xml);
}
TEST_CASE_SETUP_END

TEST_CASE_TEARDOWN()
{
	s_document.reset();
}
TEST_CASE_TEARDOWN_END

TEST_CASE("default construction initialises iterator to the end of the sequence")
{
	XML::XPathIterator end;
	XML::XPathIterator begin;

	TEST_TRUE(begin == end);
	TEST_FALSE(begin != end);
}
TEST_CASE_END

TEST_CASE("dereferencing an iterator at the sequence end throws an exception")
{
	XML::XPathIterator end;

	TEST_THROWS(*end);
}
TEST_CASE_END

TEST_CASE("advancing an iterator at the sequence end throws an exception")
{
	XML::XPathIterator end;

	TEST_THROWS(++end);

	XML::XPathIterator it(TXT("A"), s_document);

	++it;

	TEST_THROWS(++it);
}
TEST_CASE_END

TEST_CASE("the iterator can be advanced in the forward direction")
{
	XML::XPathIterator it(TXT("/"), s_document);
	XML::XPathIterator end;

	TEST_TRUE(it != end);
	++it;
	TEST_TRUE(it == end);
}
TEST_CASE_END

TEST_CASE("the XPath expression '/' returns the document root")
{
	XML::NodePtr nonRootNode = *s_document->beginChild();

	XML::XPathIterator it(TXT("/"), nonRootNode);
	XML::XPathIterator end;

	TEST_TRUE(*it == s_document);
}
TEST_CASE_END

TEST_CASE("the XPath expression 'ELEMENT' returns a sequence of elements of the same name")
{
	XML::XPathIterator it(TXT("B"), s_document->getRootElement());
	XML::XPathIterator end;

	XML::ElementNodePtr element = Core::dynamic_ptr_cast<XML::ElementNode>(*it);
	tstring				name = element->name();
	XML::AttributePtr	attribute = element->getAttributes().find(TXT("ID"));

	TEST_TRUE( (name == TXT("B")) && (attribute->value() == TXT("2.1")) );

	++it;

	element = Core::dynamic_ptr_cast<XML::ElementNode>(*it);
	name = element->name();
	attribute = element->getAttributes().find(TXT("ID"));

	TEST_TRUE( (name == TXT("B")) && (attribute->value() == TXT("2.3")) );

	++it;

	TEST_TRUE(it == end);
}
TEST_CASE_END

TEST_CASE("an XPath expression uses '/' characters to separate elements")
{
	XML::XPathIterator it(TXT("/A/C/B"), s_document->getRootElement());
	XML::XPathIterator end;

	XML::ElementNodePtr element = Core::dynamic_ptr_cast<XML::ElementNode>(*it);
	tstring				name = element->name();
	XML::AttributePtr	attribute = element->getAttributes().find(TXT("ID"));

	TEST_TRUE( (name == TXT("B")) && (attribute->value() == TXT("3")) );

	++it;

	TEST_TRUE(it == end);
}
TEST_CASE_END

}
TEST_SET_END
