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

void TestXPathIterator()
{
	XML::XPathIterator end;
	XML::XPathIterator begin;

	TEST_TRUE(begin == end);
	TEST_FALSE(begin != end);

	XML::Reader oReader;

	XML::DocumentPtr pDoc = oReader.ReadDocument(g_strXML);

{
	XML::XPathIterator it(TXT("/"), *pDoc->BeginChild());

	TEST_TRUE(*it == pDoc);
	++it;
	TEST_TRUE(it == end);
}

{
	XML::XPathIterator it(TXT("A"), pDoc);

	XML::Nodes::const_iterator it2 = pDoc->BeginChild();

	++it2;

	TEST_TRUE(*it == *it2);
}

{
	XML::XPathIterator it(TXT("/A/B"), pDoc);

	XML::ElementNodePtr p = Core::dynamic_ptr_cast<XML::ElementNode>(*it);

	TEST_TRUE((p->Name() == TXT("B")) && (p->GetAttributes().Find(TXT("ID"))->Value() == TXT("2.1")));

	++it;
	p = Core::dynamic_ptr_cast<XML::ElementNode>(*it);

	TEST_TRUE((p->Name() == TXT("B")) && (p->GetAttributes().Find(TXT("ID"))->Value() == TXT("2.3")));

	++it;
	TEST_TRUE(it == end);
}

}
