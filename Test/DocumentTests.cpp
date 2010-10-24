////////////////////////////////////////////////////////////////////////////////
//! \file   TestDocument.cpp
//! \brief  The unit tests for the Document class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/Document.hpp>
#include <XML/TextNode.hpp>
#include <XML/ElementNode.hpp>

TEST_SET(Document)
{
//	XML::Document oDoc;		// Shouldn't compile.

	const XML::DocumentPtr pDoc1(new XML::Document);

	TEST_TRUE(pDoc1->type() == XML::DOCUMENT_NODE);
	TEST_TRUE(tstrlen(pDoc1->typeStr()) != 0);

	TEST_TRUE(pDoc1->hasChildren() == false);
	TEST_TRUE(pDoc1->getChildCount() == 0);
	TEST_TRUE(pDoc1->beginChild() == pDoc1->endChild());
	TEST_TRUE(pDoc1->hasRootElement() == false);
	TEST_TRUE(pDoc1->getRootElement().get() == nullptr);

	XML::DocumentPtr pDoc(new XML::Document);

	TEST_TRUE(pDoc->beginChild() == pDoc->endChild());
	TEST_TRUE(pDoc->getRootElement().get() == nullptr);

	XML::TextNodePtr pText(new XML::TextNode(TXT("TextNode")));

	pDoc->appendChild(pText);

	TEST_TRUE(pDoc->hasChildren() == true);
	TEST_TRUE(pDoc->getChildCount() == 1);

	TEST_TRUE(pDoc->beginChild() != pDoc->endChild());
	TEST_TRUE((*pDoc->beginChild()).get() == pText.get());

	XML::Nodes::iterator itBeginChild = pDoc->beginChild();	// ++pDoc->BeginChild() fails to build in Release.

	TEST_TRUE(++itBeginChild == pDoc->endChild());

	XML::ElementNodePtr pElement(new XML::ElementNode(TXT("ElementNode")));

	pDoc->appendChild(pElement);

	TEST_TRUE(pDoc->hasChildren() == true);
	TEST_TRUE(pDoc->getChildCount() == 2);

	itBeginChild = pDoc->beginChild();	// ++pDoc->BeginChild() fails to build in Release.

	TEST_TRUE((*++itBeginChild)->type() == XML::ELEMENT_NODE);

	TEST_TRUE(pDoc->hasRootElement() == true);
	TEST_TRUE(pDoc->getRootElement() == pElement);

	TEST_THROWS(pDoc->appendChild(pElement));
	TEST_THROWS(pDoc->appendChild(pDoc));

	const XML::DocumentPtr constDoc(pDoc);

	TEST_TRUE(constDoc->getRootElement().get() != nullptr);
}
TEST_SET_END
