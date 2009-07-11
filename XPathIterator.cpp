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
	: m_itNode(m_vecNodes.end())
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a query and a document.

XPathIterator::XPathIterator(const tstring& strQuery, const NodePtr& pNode)
	: m_strQuery(strQuery)
	, m_pNode(pNode)
	, m_itNode(m_vecNodes.end())
{
	begin();
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
	if (m_itNode == m_vecNodes.end())
		throw Core::BadLogicException(TXT("Attempt to dereference an invalid XPath iterator"));

	return *m_itNode;
}

////////////////////////////////////////////////////////////////////////////////
//! Advance the iterator.

void XPathIterator::operator++()
{
	next();
}

////////////////////////////////////////////////////////////////////////////////
//! Compare two iterators for equivalence.
//! NB: As they are not copyable the only iterator they can be equivalent to is
//! an end iterator.

bool XPathIterator::equals(const XPathIterator& RHS) const
{
	return ( (m_itNode     == m_vecNodes.end())
		  && (RHS.m_itNode == RHS.m_vecNodes.end()) );
}

////////////////////////////////////////////////////////////////////////////////
//! Start the iteration.

void XPathIterator::begin()
{
	tstring::const_iterator it  = m_strQuery.begin();
	tstring::const_iterator end = m_strQuery.end();

	NodePtr pContext = m_pNode;

	// Until the entire query has been parsed.
	if (it != end)
	{
		// Is an absolute path?
		if (*it == TXT('/'))
		{
			++it;

			// Search for the document root...
			while (pContext->hasParent())
				pContext = pContext->parent();
		}

		parse(it, end, pContext);
	}

	// Start iterating the result set.
	m_itNode = m_vecNodes.begin();
}

////////////////////////////////////////////////////////////////////////////////
//! Continue the iteration.

void XPathIterator::next()
{
	if (m_itNode == m_vecNodes.end())
		throw Core::BadLogicException(TXT("Attempted to advance an invalid XPath iterator"));

	++m_itNode;
}

////////////////////////////////////////////////////////////////////////////////
//! End the iteration.

void XPathIterator::reset()
{
	m_strQuery.clear();
	m_pNode.reset();
	m_vecNodes.clear();
	m_itNode = m_vecNodes.end();
}

////////////////////////////////////////////////////////////////////////////////
//! Parse the next part of the query.

void XPathIterator::parse(QueryIterator begin, QueryIterator end, const NodePtr& pContext)
{
	// Finished parsing?
	if (begin == end)
	{
		// Add to results, if valid node.
		if (pContext.get() != nullptr)
			m_vecNodes.push_back(pContext);

		return;
	}

	// Skip path separator.
	tstring::const_iterator it = begin;

	if (*it == TXT('/'))
		++it;

	// Extract the node name.
	tstring::const_iterator itName = it;

	while ( (it != end) && (*it != TXT('/')) )
		++it;

	tstring strName(itName, it);

	NodeType       eType  = pContext->type();
	NodeContainer* pNodes = nullptr;

	// Has children?
	if (eType == DOCUMENT_NODE)
		pNodes = Core::static_ptr_cast<Document>(pContext).get();
	else if (eType == ELEMENT_NODE)
		pNodes = Core::static_ptr_cast<ElementNode>(pContext).get();

	// Find all children that match the name.
	for (NodeContainer::const_iterator itNode = pNodes->beginChild(); itNode != pNodes->endChild(); ++itNode)
	{
		const NodePtr& pNode = *itNode;

		// If a match, recurse...
		if ( (pNode->type() == ELEMENT_NODE)
			&& (Core::static_ptr_cast<ElementNode>(pNode)->name() == strName) )
		{
			parse(it, end, *itNode);
		}
	}
}

//namespace XML
}
