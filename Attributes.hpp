////////////////////////////////////////////////////////////////////////////////
//! \file   Attributes.hpp
//! \brief  The Attributes class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_ATTRIBUTES_HPP
#define XML_ATTRIBUTES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Attribute.hpp"
#include <vector>

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The collection of attributes for a node.

class Attributes
{
	//! The underlying container type.
	typedef std::vector<AttributePtr> Container;

public:
	//! Default constructor.
	Attributes();

	//! Destructor.
	~Attributes();
	
	//
	// Types.
	//

	//! The iterator type.
	typedef Container::const_iterator const_iterator;
	//! The const iterator type.
	typedef Container::iterator iterator;

	//
	// Properties.
	//

	//! Query if the collection is empty.
	bool IsEmpty() const;

	//! Query how many attributes there are.
	size_t Count() const;

	//! Get the start iterator for the collection.
	const_iterator Begin() const;

	//! Get the end iterator for the collection.
	const_iterator End() const;

	//! Get the start iterator for the collection.
	iterator Begin();

	//! Get the end iterator for the collection.
	iterator End();

	//
	// Methods.
	//

	//! Clear the set of attributes.
	void Clear();

	//! Set an attribute.
	void SetAttribute(const AttributePtr& pAttribute);

	//! Find an attribute by its name.
	AttributePtr Find(const tstring& strName) const;

	//! Get an attribute by its name or throw if not found.
	AttributePtr Get(const tstring& strName) const; // throw(InvalidArgException)

private:
	//
	// Members.
	//
	Container	m_vAttribs;		//!< The underlying container.
};

////////////////////////////////////////////////////////////////////////////////
//! Query if the collection is empty.

inline bool Attributes::IsEmpty() const
{
	return m_vAttribs.empty();
}

////////////////////////////////////////////////////////////////////////////////
//! Query how many attributes there are.

inline size_t Attributes::Count() const
{
	return m_vAttribs.size();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the start iterator for the collection.

inline Attributes::const_iterator Attributes::Begin() const
{
	return m_vAttribs.begin();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the end iterator for the collection.

inline Attributes::const_iterator Attributes::End() const
{
	return m_vAttribs.end();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the start iterator for the collection.

inline Attributes::iterator Attributes::Begin()
{
	return m_vAttribs.begin();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the end iterator for the collection.

inline Attributes::iterator Attributes::End()
{
	return m_vAttribs.end();
}

//namespace XML
}

#endif // XML_ATTRIBUTES_HPP
