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
	XPathIterator(const tstring& query, const NodePtr& context);

	//! Destructor.
	~XPathIterator();

	//
	// Operators.
	//

	//! Dereference operator.
	NodePtr operator*() const;

	//! Advance the iterator.
	XPathIterator& operator++();

	//
	// Methods.
	//

	//! Compare two iterators for equivalence.
	bool equals(const XPathIterator& rhs) const;

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
	tstring			m_query;		//!< The query.
	NodePtr			m_context;		//!< The context XML node.
	Nodes			m_results;		//!< The query results.
	NodeIterator	m_currNode;		//!< The iterator into the query results.

	//
	// Internal methods.
	//

	//! Start the iteration.
	void start();

	//! Continue the iteration.
	void next();

	//! End the iteration.
	void reset();

	//! Parse the next part of the query.
	void parse(QueryIterator begin, QueryIterator end, const NodePtr& context);
};

////////////////////////////////////////////////////////////////////////////////
//! Global equivalence operator for a XPath iterator.

inline bool operator==(const XPathIterator& lhs, const XPathIterator& rhs)
{
	return lhs.equals(rhs);
}

////////////////////////////////////////////////////////////////////////////////
//! Global non-equivalence operator for a XPath iterator.

inline bool operator!=(const XPathIterator& lhs, const XPathIterator& rhs)
{
	return !operator==(lhs, rhs);
}

//namespace XML
}

#endif // XML_XPATHITERATOR_HPP
