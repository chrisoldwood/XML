////////////////////////////////////////////////////////////////////////////////
//! \file   TestReader.cpp
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

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the Reader class.

void testReader()
{
	XML::Reader oReader;

	XML::DocumentPtr pDoc = oReader.readDocument(TXT("  <?P?>  <!DOCTYPE R>  <!---->  <R><E/></R>  "));

	TEST_TRUE(pDoc->getChildCount() == 9);
	TEST_TRUE(pDoc->getRootElement()->name() == TXT("R"));

	XML::Nodes::iterator it = pDoc->beginChild();

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

	TEST_THROWS(oReader.readDocument(TXT("")));
	TEST_THROWS(oReader.readDocument(TXT(" x <R/>")));
	TEST_THROWS(oReader.readDocument(TXT("<R/> x ")));
	TEST_THROWS(oReader.readDocument(TXT("<?\?><R/>")));	// ??> is a trigraph.
	TEST_THROWS(oReader.readDocument(TXT("<R>")));
	TEST_THROWS(oReader.readDocument(TXT("</R>")));
	TEST_THROWS(oReader.readDocument(TXT("<R><E></R>")));
	TEST_THROWS(oReader.readDocument(TXT("<R></E></R>")));

	pDoc = oReader.readDocument(TXT("<?xml version=\"1.0\" encoding=\"utf-8\"?><R/>"));

	ASSERT(pDoc->getChildCount() == 2);

	XML::ProcessingNodePtr pProcNode = Core::dynamic_ptr_cast<XML::ProcessingNode>(*pDoc->beginChild());

	TEST_TRUE(pProcNode->target() == TXT("xml"));

	const XML::Attributes& vAttribs = pProcNode->getAttributes();

	TEST_TRUE(vAttribs.isEmpty() == false);
	TEST_TRUE(vAttribs.count() == 2);

	XML::Attributes::const_iterator itAttrib = vAttribs.begin();

	TEST_TRUE((*itAttrib)->name() == TXT("version"));
	TEST_TRUE((*itAttrib)->value() == TXT("1.0"));

	++itAttrib;

	TEST_TRUE((*itAttrib)->name() == TXT("encoding"));
	TEST_TRUE((*itAttrib)->value() == TXT("utf-8"));

	TEST_THROWS(oReader.readDocument(TXT("<R a>")));
	TEST_THROWS(oReader.readDocument(TXT("<R a=>")));
	TEST_THROWS(oReader.readDocument(TXT("<R a=b>")));
	TEST_THROWS(oReader.readDocument(TXT("<R a='b>")));
	TEST_THROWS(oReader.readDocument(TXT("<R a='b\">")));

	TEST_TRUE(oReader.readDocument(TXT("<?x v = \"1.0\" encoding = 'utf-8'  ?><R a = 'b'  />")).get() != nullptr);

	const tstring strFlagsTest = TXT(" \t<?xml?><!DOCTYPE R><!----><R>\r\n</R> \t");

	pDoc = oReader.readDocument(strFlagsTest, XML::Reader::DISCARD_WHITESPACE);

	TEST_TRUE(pDoc->getChildCount() == 4);

	pDoc = oReader.readDocument(strFlagsTest, XML::Reader::DISCARD_COMMENTS);

	TEST_TRUE(pDoc->getChildCount() == 5);

	pDoc = oReader.readDocument(strFlagsTest, XML::Reader::DISCARD_PROC_INSTNS);

	TEST_TRUE(pDoc->getChildCount() == 5);

	pDoc = oReader.readDocument(strFlagsTest, XML::Reader::DISCARD_DOC_TYPES);

	TEST_TRUE(pDoc->getChildCount() == 5);

	TEST_THROWS(oReader.readDocument(TXT("<!")));
	TEST_THROWS(oReader.readDocument(TXT("<!-")));

	TEST_TRUE(oReader.readDocument(TXT("<!DOCTYPE root PUBLIC \"http://\"[<!-- comment -->]><root/>")).get() != nullptr);

	TEST_TRUE(oReader.readDocument(TXT("<root a=\"<>\" b='<>' />")).get() != nullptr);

	TEST_TRUE(oReader.readDocument(TXT("<!-- <> -> -- --><root/>")).get() != nullptr);

	TEST_TRUE(oReader.readDocument(TXT("<root> <![CDATA[ ]]> </root>")).get() != nullptr);
}
