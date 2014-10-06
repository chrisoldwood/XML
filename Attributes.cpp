////////////////////////////////////////////////////////////////////////////////
//! \file   Attributes.cpp
//! \brief  The Attributes class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Attributes.hpp"
#include <Core/InvalidArgException.hpp>
#include <Core/StringUtils.hpp>
#include <algorithm>

#ifdef __GNUG__
// base class 'X' has a non-virtual destructor
#pragma GCC diagnostic ignored "-Weffc++"
#endif

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The predicate used to find an attribute by name.

struct FindByName : public std::unary_function<AttributePtr, bool>
{
	//! The string to match.
	tstring	m_str;

	//! Constructor.
	FindByName(const tstring& str)
		: m_str(str)
	{
	}

	//! Compare the attribute name for a match.
	bool operator()(const AttributePtr& attribute)
	{
		return (attribute->name() == m_str);
	}
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Attributes::Attributes()
	: m_attributes()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction with a single attribute.

Attributes::Attributes(AttributePtr attribute)
	: m_attributes()
{
	m_attributes.push_back(attribute);
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Attributes::~Attributes()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Clear the set of attributes.

void Attributes::clear()
{
	m_attributes.clear();
}

////////////////////////////////////////////////////////////////////////////////
//! Set an attribute. If the attribute name already exists in the collection
//! it replaces it, otherwise it is appeneded.

void Attributes::setAttribute(const AttributePtr& attribute)
{
	if (attribute->name().empty())
		throw Core::InvalidArgException(TXT("Failed to set an attribute as the name is empty"));

	// Replace value or append attribute to collection.
	AttributePtr existing = find(attribute->name());

	if (existing.get() != nullptr)
		existing->setValue(attribute->value());
	else
		m_attributes.push_back(attribute);
}

////////////////////////////////////////////////////////////////////////////////
//! Find an attribute by its name.

AttributePtr Attributes::find(const tstring& name) const
{
	AttributePtr attribute;

	Container::const_iterator it = std::find_if(m_attributes.begin(), m_attributes.end(), FindByName(name));

	if (it != m_attributes.end())
		attribute = *it;

	return attribute;
}

////////////////////////////////////////////////////////////////////////////////
//! Get an attribute by its name or throw if not found.

AttributePtr Attributes::get(const tstring& name) const
{
	AttributePtr attribute = find(name);

	if (attribute.get() == nullptr)
		throw Core::InvalidArgException(Core::fmt(TXT("Failed to retrieve attribute '%s'"), name.c_str()));

	return attribute;
}

//namespace XML
}
