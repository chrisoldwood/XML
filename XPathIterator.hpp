////////////////////////////////////////////////////////////////////////////////
//! \file   XPathIterator.hpp
//! \brief  The XPathIterator class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_XPATHITERATOR_HPP
#define XML_XPATHITERATOR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Document.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! An iterator for enumerating an XML document according to an XPath
//! expression. To keep the code simple the iterator runs the entire query up
//! front and just iterates the results.

class XPathIterator : private Core::NotCopyable
{
public:
	//! Default constructor.
	XPathIterator();

	//! Construction from a query and a context node.
	XPathIterator(const tstring& strQuery, const NodePtr& pNode);

	//! Destructor.
	~XPathIterator();
	
	//
	// Operators.
	//

	//! Dereference operator.
	NodePtr operator*() const;

	//! Advance the iterator.
	void operator++();

	//
	// Methods.
	//

	//! Compare two iterators for equivalence.
	bool Equals(const XPathIterator& RHS) const;

private:
	//! The results container type.
	typedef std::vector<NodePtr> Nodes;
	//! The results container iterator type.
	typedef Nodes::const_iterator NodeIterator;
	//! The query iterator type.
	typedef tstring::const_iterator QueryIterator;

	//
	// Members.
	//
	tstring			m_strQuery;		//!< The query.
	NodePtr			m_pNode;		//!< The context XML node.
	Nodes			m_vecNodes;		//!< The query results.
	NodeIterator	m_itNode;		//!< The iterator into the query results.

	//
	// Internal methods.
	//

	//! Start the iteration.
	void Begin();

	//! Continue the iteration.
	void Next();

	//! End the iteration.
	void Reset();

	//! Parse the next part of the query.
	void Parse(QueryIterator begin, QueryIterator end, const NodePtr& pContext);
};

////////////////////////////////////////////////////////////////////////////////
//! Global equivalence operator for a XPath iterator.

inline bool operator==(const XPathIterator& LHS, const XPathIterator& RHS)
{
	return LHS.Equals(RHS);
}

////////////////////////////////////////////////////////////////////////////////
//! Global non-equivalence operator for a XPath iterator.

inline bool operator!=(const XPathIterator& LHS, const XPathIterator& RHS)
{
	return !operator==(LHS, RHS);
}

//namespace XML
}

#endif // XML_XPATHITERATOR_HPP
