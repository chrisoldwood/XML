////////////////////////////////////////////////////////////////////////////////
//! \file   DocumentTests.cpp
//! \brief  The unit tests for the Document class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <XML/Document.hpp>
#include <XML/TextNode.hpp>
#include <XML/ElementNode.hpp>

TEST_SET(Document)
{

TEST_CASE("compilation only succeeds for construction on the heap")
{
//	XML::Document stackNode;		// Shouldn't compile.

	XML::DocumentPtr heapNode(new XML::Document);

	TEST_PASSED("compilation succeeds");
}
TEST_CASE_END

TEST_CASE("type returns the type of the node as an enumeration value")
{
	XML::DocumentPtr node(new XML::Document);

	TEST_TRUE(node->type() == XML::DOCUMENT_NODE);
	TEST_TRUE(tstricmp(node->typeStr(), TXT("document")) == 0);
}
TEST_CASE_END

TEST_CASE("initial document is empty")
{
	const XML::DocumentPtr constDocument(new XML::Document);

	TEST_TRUE(constDocument->hasChildren() == false);
	TEST_TRUE(constDocument->getChildCount() == 0);
	TEST_TRUE(constDocument->beginChild() == constDocument->endChild());
	TEST_TRUE(constDocument->hasRootElement() == false);
	TEST_TRUE(constDocument->getRootElement().get() == nullptr);

	XML::DocumentPtr nonConstDocument(new XML::Document);

	TEST_TRUE(nonConstDocument->beginChild() == nonConstDocument->endChild());
	TEST_TRUE(nonConstDocument->getRootElement().get() == nullptr);
}
TEST_CASE_END

TEST_CASE("appending a child node creates a non-empty node sequence")
{
	XML::DocumentPtr document(new XML::Document);
	XML::TextNodePtr textNode(new XML::TextNode(TXT("TextNode")));

	document->appendChild(textNode);

	TEST_TRUE(document->hasChildren() == true);
	TEST_TRUE(document->getChildCount() == 1);

	TEST_TRUE(document->beginChild() != document->endChild());

	XML::NodeContainer::iterator firstChild = document->beginChild();

	TEST_TRUE((*firstChild).get() == textNode.get());

	XML::Nodes::iterator endChild = document->endChild();	// ++pDoc->BeginChild() fails to build in Release.

	TEST_TRUE(++firstChild == endChild);
}
TEST_CASE_END

TEST_CASE("appending an element node gives the document a root element")
{
	XML::DocumentPtr document(new XML::Document);
	XML::TextNodePtr nonElelementNode(new XML::TextNode(TXT("TextNode")));

	document->appendChild(nonElelementNode);

	TEST_TRUE(document->hasRootElement() == false);
	TEST_TRUE(document->getRootElement().get() == nullptr);

	XML::ElementNodePtr elementNode(new XML::ElementNode(TXT("ElementNode")));

	document->appendChild(elementNode);

	TEST_TRUE(document->hasRootElement() == true);
	TEST_TRUE(document->getRootElement() == elementNode);
}
TEST_CASE_END

TEST_CASE("a document can be constructed with a root element")
{
	XML::ElementNodePtr root(new XML::ElementNode(TXT("root")));
	XML::DocumentPtr document(new XML::Document(root));

	TEST_TRUE(document->hasRootElement() == true);
	TEST_TRUE(document->getRootElement() == root);
}
TEST_CASE_END

TEST_CASE("an empty document can be made via a helper")
{
	XML::DocumentPtr document = XML::makeDocument();

	TEST_TRUE(document->hasRootElement() == false);
}
TEST_CASE_END

TEST_CASE("a document with a root element can be made via a helper")
{
	XML::DocumentPtr document = XML::makeDocument
	(
		XML::makeElement(TXT("root"))
	);

	TEST_TRUE(document->hasRootElement() == true);
	TEST_TRUE(document->getRootElement()->name() == TXT("root"));
}
TEST_CASE_END

}
TEST_SET_END
