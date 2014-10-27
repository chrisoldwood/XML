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

	//! Construction with a single attribute.
	Attributes(AttributePtr attribute);

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
	bool isEmpty() const;

	//! Query how many attributes there are.
	size_t count() const;

	//! Get the start iterator for the collection.
	const_iterator begin() const;

	//! Get the end iterator for the collection.
	const_iterator end() const;

	//! Get the start iterator for the collection.
	iterator begin();

	//! Get the end iterator for the collection.
	iterator end();

	//
	// Methods.
	//

	//! Clear the set of attributes.
	void clear();

	//! Set an attribute.
	void setAttribute(const AttributePtr& attribute);

	//! Set an attribute from the name/value pair.
	void setAttribute(const tstring& name, const tstring& value);

	//! Find an attribute by its name.
	AttributePtr find(const tstring& name) const;

	//! Get an attribute by its name or throw if not found.
	AttributePtr get(const tstring& name) const; // throw(InvalidArgException)

private:
	//
	// Members.
	//
	Container	m_attributes;		//!< The underlying container.
};

////////////////////////////////////////////////////////////////////////////////
//! Query if the collection is empty.

inline bool Attributes::isEmpty() const
{
	return m_attributes.empty();
}

////////////////////////////////////////////////////////////////////////////////
//! Query how many attributes there are.

inline size_t Attributes::count() const
{
	return m_attributes.size();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the start iterator for the collection.

inline Attributes::const_iterator Attributes::begin() const
{
	return m_attributes.begin();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the end iterator for the collection.

inline Attributes::const_iterator Attributes::end() const
{
	return m_attributes.end();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the start iterator for the collection.

inline Attributes::iterator Attributes::begin()
{
	return m_attributes.begin();
}

////////////////////////////////////////////////////////////////////////////////
//! Get the end iterator for the collection.

inline Attributes::iterator Attributes::end()
{
	return m_attributes.end();
}

//namespace XML
}

#endif // XML_ATTRIBUTES_HPP
