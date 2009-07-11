////////////////////////////////////////////////////////////////////////////////
//! \file   TestXPathIterator.cpp
//! \brief  The unit tests for the XPathIterator class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/XPathIterator.hpp>
#include <XML/Reader.hpp>

static const tstring g_strXML =	TXT("<?xml version='1.0' ?>")
								TXT("<A ID='1'>")
								TXT("    <B ID='2.1'/>")
								TXT("    <C ID='2.2'>")
								TXT("        <B ID='3'/>")
								TXT("    </C>")
								TXT("    <B ID='2.3'/>")
								TXT("</A>");

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the XPathIterator class.

void testXPathIterator()
{
	XML::XPathIterator end;
	XML::XPathIterator begin;

	TEST_TRUE(begin == end);
	TEST_FALSE(begin != end);

	XML::Reader oReader;

	XML::DocumentPtr pDoc = oReader.readDocument(g_strXML);

{
	XML::XPathIterator it(TXT("/"), *pDoc->beginChild());

	TEST_TRUE(*it == pDoc);
	++it;
	TEST_TRUE(it == end);
}

{
	XML::XPathIterator it(TXT("A"), pDoc);

	XML::Nodes::const_iterator it2 = pDoc->beginChild();

	++it2;

	TEST_TRUE(*it == *it2);
}

{
	XML::XPathIterator it(TXT("/A/B"), pDoc);

	XML::ElementNodePtr p = Core::dynamic_ptr_cast<XML::ElementNode>(*it);

	TEST_TRUE((p->name() == TXT("B")) && (p->getAttributes().find(TXT("ID"))->value() == TXT("2.1")));

	++it;
	p = Core::dynamic_ptr_cast<XML::ElementNode>(*it);

	TEST_TRUE((p->name() == TXT("B")) && (p->getAttributes().find(TXT("ID"))->value() == TXT("2.3")));

	++it;
	TEST_TRUE(it == end);
}

}
