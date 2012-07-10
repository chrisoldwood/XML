////////////////////////////////////////////////////////////////////////////////
//! \file   XPathIterator.cpp
//! \brief  The XPathIterator class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "XPathIterator.hpp"
#include <Core/BadLogicException.hpp>

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

XPathIterator::XPathIterator()
	: m_query()
	, m_context()
	, m_results()
	, m_currNode(m_results.end())
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a query and a document.

XPathIterator::XPathIterator(const tstring& query, const NodePtr& context)
	: m_query(query)
	, m_context(context)
	, m_results()
	, m_currNode(m_results.end())
{
	start();
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

XPathIterator::~XPathIterator()
{
	reset();
}

////////////////////////////////////////////////////////////////////////////////
//! Dereference operator.

NodePtr XPathIterator::operator*() const
{
	if (m_currNode == m_results.end())
		throw Core::BadLogicException(TXT("Attempt to dereference an invalid XPath iterator"));

	return *m_currNode;
}

////////////////////////////////////////////////////////////////////////////////
//! Advance the iterator.

XPathIterator& XPathIterator::operator++()
{
	next();

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//! Compare two iterators for equivalence.
//! NB: As they are not copyable the only iterator they can be equivalent to is
//! an end iterator.

bool XPathIterator::equals(const XPathIterator& rhs) const
{
	return ( (m_currNode     == m_results.end())
		  && (rhs.m_currNode == rhs.m_results.end()) );
}

////////////////////////////////////////////////////////////////////////////////
//! Start the iteration.

void XPathIterator::start()
{
	tstring::const_iterator it  = m_query.begin();
	tstring::const_iterator end = m_query.end();

	NodePtr context = m_context;

	// Until the entire query has been parsed.
	if (it != end)
	{
		// Is an absolute path?
		if (*it == TXT('/'))
		{
			++it;

			// Search for the document root...
			while (context->hasParent())
				context = context->parent();
		}

		parse(it, end, context);
	}

	// Start iterating the result set.
	m_currNode = m_results.begin();
}

////////////////////////////////////////////////////////////////////////////////
//! Continue the iteration.

void XPathIterator::next()
{
	if (m_currNode == m_results.end())
		throw Core::BadLogicException(TXT("Attempted to advance an invalid XPath iterator"));

	++m_currNode;
}

////////////////////////////////////////////////////////////////////////////////
//! End the iteration.

void XPathIterator::reset()
{
	m_query.clear();
	m_context.reset();
	m_results.clear();
	m_currNode = m_results.end();
}

////////////////////////////////////////////////////////////////////////////////
//! Parse the next part of the query.

void XPathIterator::parse(QueryIterator begin, QueryIterator end, const NodePtr& context)
{
	// Finished parsing?
	if (begin == end)
	{
		// Add to results, if valid node.
		if (context.get() != nullptr)
			m_results.push_back(context);

		return;
	}

	// Skip path separator.
	tstring::const_iterator it = begin;

	if (*it == TXT('/'))
		++it;

	// Extract the node name.
	tstring::const_iterator nameFirst = it;

	while ( (it != end) && (*it != TXT('/')) )
		++it;

	tstring name(nameFirst, it);

	NodeType       type  = context->type();
	NodeContainer* nodes = nullptr;

	// Has children?
	if (type == DOCUMENT_NODE)
		nodes = Core::static_ptr_cast<Document>(context).get();
	else if (type == ELEMENT_NODE)
		nodes = Core::static_ptr_cast<ElementNode>(context).get();

	// Find all children that match the name.
	for (NodeContainer::const_iterator nodeIter = nodes->beginChild(); nodeIter != nodes->endChild(); ++nodeIter)
	{
		const NodePtr& node = *nodeIter;

		// If a match, recurse...
		if ( (node->type() == ELEMENT_NODE)
			&& (Core::static_ptr_cast<ElementNode>(node)->name() == name) )
		{
			parse(it, end, *nodeIter);
		}
	}
}

//namespace XML
}
