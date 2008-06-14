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

void TestReader()
{
	XML::Reader oReader;

	XML::DocumentPtr pDoc = oReader.ReadDocument(TXT("  <?P?>  <!DOCTYPE R>  <!---->  <R><E/></R>  "));

	TEST_TRUE(pDoc->GetChildCount() == 9);
	TEST_TRUE(pDoc->GetRootElement()->Name() == TXT("R"));

	XML::Nodes::iterator it = pDoc->BeginChild();

	TEST_TRUE((*it)->Type() == XML::TEXT_NODE);
	TEST_TRUE(Core::dynamic_ptr_cast<XML::TextNode>(*it)->Text() == TXT("  "));

	++it;

	TEST_TRUE((*it)->Type() == XML::PROCESSING_NODE);
	TEST_TRUE(Core::dynamic_ptr_cast<XML::ProcessingNode>(*it)->Target() == TXT("P"));

	it += 2;

	TEST_TRUE((*it)->Type() == XML::DOCTYPE_NODE);
	TEST_TRUE(Core::dynamic_ptr_cast<XML::DocTypeNode>(*it)->Declaration() == TXT(" R"));

	it += 2;

	TEST_TRUE((*it)->Type() == XML::COMMENT_NODE);
	TEST_TRUE(Core::dynamic_ptr_cast<XML::CommentNode>(*it)->Comment() == TXT(""));

	it += 2;

	TEST_TRUE((*it)->Type() == XML::ELEMENT_NODE);

	XML::ElementNodePtr pElement = Core::dynamic_ptr_cast<XML::ElementNode>(*it);

	TEST_TRUE(pElement->Name() == TXT("R"));
	TEST_TRUE(pElement->GetChildCount() == 1);
	TEST_TRUE(Core::dynamic_ptr_cast<XML::ElementNode>(*pElement->BeginChild())->Name() == TXT("E"));

	TEST_THROWS(oReader.ReadDocument(TXT("")));
	TEST_THROWS(oReader.ReadDocument(TXT(" x <R/>")));
	TEST_THROWS(oReader.ReadDocument(TXT("<R/> x ")));
	TEST_THROWS(oReader.ReadDocument(TXT("<?\?><R/>")));	// ??> is a trigraph.
	TEST_THROWS(oReader.ReadDocument(TXT("<R>")));
	TEST_THROWS(oReader.ReadDocument(TXT("</R>")));
	TEST_THROWS(oReader.ReadDocument(TXT("<R><E></R>")));
	TEST_THROWS(oReader.ReadDocument(TXT("<R></E></R>")));

	pDoc = oReader.ReadDocument(TXT("<?xml version=\"1.0\" encoding=\"utf-8\"?><R/>"));

	ASSERT(pDoc->GetChildCount() == 2);

	XML::ProcessingNodePtr pProcNode = Core::dynamic_ptr_cast<XML::ProcessingNode>(*pDoc->BeginChild());

	TEST_TRUE(pProcNode->Target() == TXT("xml"));

	const XML::Attributes& vAttribs = pProcNode->GetAttributes();

	TEST_TRUE(vAttribs.IsEmpty() == false);
	TEST_TRUE(vAttribs.Count() == 2);

	XML::Attributes::const_iterator itAttrib = vAttribs.Begin();

	TEST_TRUE((*itAttrib)->Name() == TXT("version"));
	TEST_TRUE((*itAttrib)->Value() == TXT("1.0"));

	++itAttrib;

	TEST_TRUE((*itAttrib)->Name() == TXT("encoding"));
	TEST_TRUE((*itAttrib)->Value() == TXT("utf-8"));

	TEST_THROWS(oReader.ReadDocument(TXT("<R a>")));
	TEST_THROWS(oReader.ReadDocument(TXT("<R a=>")));
	TEST_THROWS(oReader.ReadDocument(TXT("<R a=b>")));
	TEST_THROWS(oReader.ReadDocument(TXT("<R a='b>")));
	TEST_THROWS(oReader.ReadDocument(TXT("<R a='b\">")));

	TEST_TRUE(oReader.ReadDocument(TXT("<?x v = \"1.0\" encoding = 'utf-8'  ?><R a = 'b'  />")).Get() != nullptr);

	const tstring strFlagsTest = TXT(" \t<?xml?><!DOCTYPE R><!----><R>\r\n</R> \t");

	pDoc = oReader.ReadDocument(strFlagsTest, XML::Reader::DISCARD_WHITESPACE);

	TEST_TRUE(pDoc->GetChildCount() == 4);

	pDoc = oReader.ReadDocument(strFlagsTest, XML::Reader::DISCARD_COMMENTS);

	TEST_TRUE(pDoc->GetChildCount() == 5);

	pDoc = oReader.ReadDocument(strFlagsTest, XML::Reader::DISCARD_PROC_INSTNS);

	TEST_TRUE(pDoc->GetChildCount() == 5);

	pDoc = oReader.ReadDocument(strFlagsTest, XML::Reader::DISCARD_DOC_TYPES);

	TEST_TRUE(pDoc->GetChildCount() == 5);

	TEST_THROWS(oReader.ReadDocument(TXT("<!")));
	TEST_THROWS(oReader.ReadDocument(TXT("<!-")));

	TEST_TRUE(oReader.ReadDocument(TXT("<!DOCTYPE root PUBLIC \"http://\"[<!-- comment -->]><root/>")).Get() != nullptr);

	TEST_TRUE(oReader.ReadDocument(TXT("<root a=\"<>\" b='<>' />")).Get() != nullptr);

	TEST_TRUE(oReader.ReadDocument(TXT("<!-- <> -> -- --><root/>")).Get() != nullptr);

	TEST_TRUE(oReader.ReadDocument(TXT("<root> <![CDATA[ ]]> </root>")).Get() != nullptr);
}
