////////////////////////////////////////////////////////////////////////////////
//! \file   TestDocument.cpp
//! \brief  The unit tests for the Document class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/Document.hpp>
#include <XML/TextNode.hpp>
#include <XML/ElementNode.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the Document class.

void TestDocument()
{
//	XML::Document oDoc;		// Shouldn't compile.

	const XML::DocumentPtr pDoc1(new XML::Document);

	TEST_TRUE(pDoc1->HasChildren() == false);
	TEST_TRUE(pDoc1->GetChildCount() == 0);
	TEST_TRUE(pDoc1->BeginChild() == pDoc1->EndChild());
	TEST_TRUE(pDoc1->HasRootElement() == false);
	TEST_TRUE(pDoc1->GetRootElement().Get() == nullptr);

	XML::DocumentPtr pDoc(new XML::Document);

	TEST_TRUE(pDoc->BeginChild() == pDoc->EndChild());
	TEST_TRUE(pDoc->GetRootElement().Get() == nullptr);

	XML::TextNodePtr pText(new XML::TextNode(TXT("TextNode")));

	pDoc->AppendChild(pText);

	TEST_TRUE(pDoc->HasChildren() == true);
	TEST_TRUE(pDoc->GetChildCount() == 1);

	TEST_TRUE(pDoc->BeginChild() != pDoc->EndChild());
	TEST_TRUE((*pDoc->BeginChild()).Get() == pText.Get());
	TEST_TRUE(++pDoc->BeginChild() == pDoc->EndChild());

	XML::ElementNodePtr pElement(new XML::ElementNode(TXT("ElementNode")));

	pDoc->AppendChild(pElement);

	TEST_TRUE(pDoc->HasChildren() == true);
	TEST_TRUE(pDoc->GetChildCount() == 2);
	TEST_TRUE((*++pDoc->BeginChild())->Type() == XML::ELEMENT_NODE);

	TEST_THROWS(pDoc->AppendChild(pElement));
	TEST_THROWS(pDoc->AppendChild(pDoc));
}
