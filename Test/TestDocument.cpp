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

void testDocument()
{
//	XML::Document oDoc;		// Shouldn't compile.

	const XML::DocumentPtr pDoc1(new XML::Document);

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
}
