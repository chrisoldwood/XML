////////////////////////////////////////////////////////////////////////////////
//! \file   ReaderTests.cpp
//! \brief  The unit tests for the Reader class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/Reader.hpp>
#include <XML/TextNode.hpp>
#include <XML/ElementNode.hpp>
#include <XML/CommentNode.hpp>
#include <XML/ProcessingNode.hpp>
#include <XML/DocTypeNode.hpp>

typedef Core::SharedPtr<XML::Reader> ReaderPtr;

static ReaderPtr s_reader;

TEST_SET(Reader)
{
TEST_CASE_SETUP()
{
	s_reader = ReaderPtr(new XML::Reader);
}
TEST_CASE_SETUP_END

TEST_CASE_TEARDOWN()
{
	s_reader.reset();
}
TEST_CASE_TEARDOWN_END

TEST_CASE("empty xml document throws an exception")
{
	TEST_THROWS(s_reader->readDocument(TXT("")));
}
TEST_CASE_END

TEST_CASE("malformed tag throws an exception")
{
	TEST_THROWS(s_reader->readDocument(TXT("<>")));
	TEST_THROWS(s_reader->readDocument(TXT("<+>")));
}
TEST_CASE_END

TEST_CASE("text node before or after the root element throws an exception")
{
	TEST_THROWS(s_reader->readDocument(TXT(" x <R/>")));

	TEST_THROWS(s_reader->readDocument(TXT("<R/> x ")));
}
TEST_CASE_END

TEST_CASE("malformed processing instruction throws an exception")
{
	TEST_THROWS(s_reader->readDocument(TXT("<?")));	// ??> is a trigraph.

	TEST_THROWS(s_reader->readDocument(TXT("<?\?><R/>")));	// ??> is a trigraph.
}
TEST_CASE_END

TEST_CASE("unopened or unclosed element tag throws an exception")
{
	TEST_THROWS(s_reader->readDocument(TXT("<R>")));

	TEST_THROWS(s_reader->readDocument(TXT("</R>")));
}
TEST_CASE_END

TEST_CASE("nested unopened or unclosed element tag throws an exception")
{
	TEST_THROWS(s_reader->readDocument(TXT("<R><E></R>")));

	TEST_THROWS(s_reader->readDocument(TXT("<R></E></R>")));
}
TEST_CASE_END

TEST_CASE("malformed attribute throws an exception")
{
	TEST_THROWS(s_reader->readDocument(TXT("<R a>")));
	TEST_THROWS(s_reader->readDocument(TXT("<R +>")));
	TEST_THROWS(s_reader->readDocument(TXT("<R a=>")));
}
TEST_CASE_END

TEST_CASE("missing or mismatched attribute quotes throws an exception")
{
	TEST_THROWS(s_reader->readDocument(TXT("<R a=b>")));
	TEST_THROWS(s_reader->readDocument(TXT("<R a='b>")));
	TEST_THROWS(s_reader->readDocument(TXT("<R a=\"b>")));
	TEST_THROWS(s_reader->readDocument(TXT("<R a='b\">")));
	TEST_THROWS(s_reader->readDocument(TXT("<R a=\"b'>")));
}
TEST_CASE_END

TEST_CASE("attribute list can use different quote types on different attributes")
{
	const tchar*     xml = TXT("<root d=\"double\" s='single' />");
	XML::DocumentPtr document = s_reader->readDocument(xml);

	XML::NodeContainer::const_iterator it = document->beginChild();
	XML::ElementNodePtr	               element = Core::dynamic_ptr_cast<XML::ElementNode>(*it);

	TEST_TRUE(element->getAttributes().get(TXT("d"))->value() == TXT("double"));
	TEST_TRUE(element->getAttributes().get(TXT("s"))->value() == TXT("single"));
}
TEST_CASE_END

TEST_CASE("attribute can contain embedded angle brackets")
{
	const tchar*     xml = TXT("<root brackets='<>' />");
	XML::DocumentPtr document = s_reader->readDocument(xml);

	XML::NodeContainer::const_iterator it = document->beginChild();
	XML::ElementNodePtr	               element = Core::dynamic_ptr_cast<XML::ElementNode>(*it);

	TEST_TRUE(element->getAttributes().get(TXT("brackets"))->value() == TXT("<>"));
}
TEST_CASE_END

TEST_CASE("malformed comment tag throws an exception")
{
	TEST_THROWS(s_reader->readDocument(TXT("<!")));
	TEST_THROWS(s_reader->readDocument(TXT("<!-")));
	TEST_THROWS(s_reader->readDocument(TXT("<!-->")));
}
TEST_CASE_END

TEST_CASE("comment tag can contain embedded dashes and angle brackets")
{
	const tchar*     xml = TXT("<!-- <> -> -- --><root/>");
	XML::DocumentPtr document = s_reader->readDocument(xml);

	XML::NodeContainer::const_iterator it = document->beginChild();
	XML::CommentNodePtr	               comment = Core::dynamic_ptr_cast<XML::CommentNode>(*it);

	TEST_TRUE(comment->comment().find_first_of(TXT("<>")) != tstring::npos);
}
TEST_CASE_END

TEST_CASE("malformed document type tag throws an exception")
{
	TEST_THROWS(s_reader->readDocument(TXT("<!")));
	TEST_THROWS(s_reader->readDocument(TXT("<!D")));
	TEST_THROWS(s_reader->readDocument(TXT("<!D>")));
}
TEST_CASE_END

TEST_CASE("document type tag can contain embedded xml")
{
	const tchar*     xml = TXT("<!DOCTYPE root PUBLIC \"http://\"[<!-- comment -->]><root/>");
	XML::DocumentPtr document = s_reader->readDocument(xml);

	XML::NodeContainer::const_iterator it = document->beginChild();
	XML::DocTypeNodePtr	               docType = Core::dynamic_ptr_cast<XML::DocTypeNode>(*it);

	TEST_TRUE(docType->declaration().find_first_of(TXT("comment")) != tstring::npos);
}
TEST_CASE_END

TEST_CASE("malformed CDATA section throws an exception")
{
	TEST_THROWS(s_reader->readDocument(TXT("<![CDATA")));
	TEST_THROWS(s_reader->readDocument(TXT("<![ ]]>")));
}
TEST_CASE_END

TEST_CASE("CDATA section can contain embedded xml")
{
	TEST_TRUE(s_reader->readDocument(TXT("<root> <![CDATA[ <> ]]> </root>")).get() != nullptr);
}
TEST_CASE_END

TEST_CASE("xml declaration can contain version and encoding attributes")
{
	const tchar*     xml = TXT("<?xml version=\"1.0\" encoding=\"utf-8\"?><R/>");
	XML::DocumentPtr document = s_reader->readDocument(xml);

	XML::ProcessingNodePtr declaration = Core::dynamic_ptr_cast<XML::ProcessingNode>(*document->beginChild());

	TEST_TRUE(declaration->target() == TXT("xml"));

	const XML::Attributes& attributes = declaration->getAttributes();

	TEST_TRUE(attributes.count() == 2);

	XML::Attributes::const_iterator it = attributes.begin();
	XML::AttributePtr attribute = *it;

	TEST_TRUE(attribute->name() == TXT("version"));
	TEST_TRUE(attribute->value() == TXT("1.0"));

	attribute = *(++it);

	TEST_TRUE(attribute->name() == TXT("encoding"));
	TEST_TRUE(attribute->value() == TXT("utf-8"));
}
TEST_CASE_END

TEST_CASE("child tag order maintained")
{
	XML::DocumentPtr document = s_reader->readDocument(TXT("  <?P?>  <!DOCTYPE R>  <!---->  <R><E/></R>  "));

	TEST_TRUE(document->getChildCount() == 9);
	TEST_TRUE(document->getRootElement()->name() == TXT("R"));

	XML::Nodes::iterator it = document->beginChild();

	TEST_TRUE((*it)->type() == XML::TEXT_NODE);
	TEST_TRUE(Core::dynamic_ptr_cast<XML::TextNode>(*it)->text() == TXT("  "));

	++it;

	TEST_TRUE((*it)->type() == XML::PROCESSING_NODE);
	TEST_TRUE(Core::dynamic_ptr_cast<XML::ProcessingNode>(*it)->target() == TXT("P"));

	it += 2;

	TEST_TRUE((*it)->type() == XML::DOCTYPE_NODE);
	TEST_TRUE(Core::dynamic_ptr_cast<XML::DocTypeNode>(*it)->declaration() == TXT(" R"));

	it += 2;

	TEST_TRUE((*it)->type() == XML::COMMENT_NODE);
	TEST_TRUE(Core::dynamic_ptr_cast<XML::CommentNode>(*it)->comment() == TXT(""));

	it += 2;

	TEST_TRUE((*it)->type() == XML::ELEMENT_NODE);

	XML::ElementNodePtr pElement = Core::dynamic_ptr_cast<XML::ElementNode>(*it);

	TEST_TRUE(pElement->name() == TXT("R"));
	TEST_TRUE(pElement->getChildCount() == 1);
	TEST_TRUE(Core::dynamic_ptr_cast<XML::ElementNode>(*pElement->beginChild())->name() == TXT("E"));
}
TEST_CASE_END

TEST_CASE("tags can contain extra whitespace")
{
	XML::DocumentPtr document = s_reader->readDocument(TXT("<?x v = \"1.0\" encoding = 'utf-8'  ?><R a = 'b'  />"));

	TEST_TRUE(document->getChildCount() == 2);

	XML::NodeContainer::const_iterator it = document->beginChild();

	XML::ProcessingNodePtr declaration = Core::dynamic_ptr_cast<XML::ProcessingNode>(*it);

	TEST_TRUE(declaration->getAttributes().count() == 2);

	XML::ElementNodePtr element = Core::dynamic_ptr_cast<XML::ElementNode>(*(++it));

	TEST_TRUE(element->getAttributes().count() == 1);
}
TEST_CASE_END

TEST_CASE("insignificant whitespace can be discarded during parsing")
{
	const tstring xml = TXT(" \t<?xml?><!DOCTYPE R><!----><R>\r\n</R> \t");

	XML::DocumentPtr document = s_reader->readDocument(xml, XML::Reader::DISCARD_WHITESPACE);

	TEST_TRUE(document->getChildCount() == 4);
}
TEST_CASE_END

TEST_CASE("comments can be discarded during parsing")
{
	const tstring xml = TXT(" \t<?xml?><!DOCTYPE R><!----><R>\r\n</R> \t");

	XML::DocumentPtr document = s_reader->readDocument(xml, XML::Reader::DISCARD_COMMENTS);

	TEST_TRUE(document->getChildCount() == 5);

}
TEST_CASE_END

TEST_CASE("processing instructions can be discarded during parsing")
{
	const tstring xml = TXT(" \t<?xml?><!DOCTYPE R><!----><R>\r\n</R> \t");

	XML::DocumentPtr document = s_reader->readDocument(xml, XML::Reader::DISCARD_PROC_INSTNS);

	TEST_TRUE(document->getChildCount() == 5);
}
TEST_CASE_END

TEST_CASE("the document type can be discarded during parsing")
{
	const tstring xml = TXT(" \t<?xml?><!DOCTYPE R><!----><R>\r\n</R> \t");

	XML::DocumentPtr document = s_reader->readDocument(xml, XML::Reader::DISCARD_DOC_TYPES);

	TEST_TRUE(document->getChildCount() == 5);
}
TEST_CASE_END

}
TEST_SET_END
