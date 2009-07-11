////////////////////////////////////////////////////////////////////////////////
//! \file   Attributes.cpp
//! \brief  The Attributes class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Attributes.hpp"
#include <Core/InvalidArgException.hpp>
#include <Core/StringUtils.hpp>
#include <algorithm>

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
	bool operator()(const AttributePtr& pAttribute)
	{
		return (pAttribute->name() == m_str);
	}
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Attributes::Attributes()
{
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
	m_vAttribs.clear();
}

////////////////////////////////////////////////////////////////////////////////
//! Set an attribute. If the attribute name already exists in the collection
//! it replaces it, otherwise it is appeneded.

void Attributes::setAttribute(const AttributePtr& pAttribute)
{
	if (pAttribute->name().empty())
		throw Core::InvalidArgException(TXT("Failed to set an attribute as the name is empty"));

	// Replace value or append attribute to collection.
	AttributePtr pExisting = find(pAttribute->name());

	if (pExisting.get() != nullptr)
		pExisting->setValue(pAttribute->value());
	else
		m_vAttribs.push_back(pAttribute);
}

////////////////////////////////////////////////////////////////////////////////
//! Find an attribute by its name.

AttributePtr Attributes::find(const tstring& strName) const
{
	AttributePtr pAttribute;

	Container::const_iterator it = std::find_if(m_vAttribs.begin(), m_vAttribs.end(), FindByName(strName));

	if (it != m_vAttribs.end())
		pAttribute = *it;

	return pAttribute;
}

////////////////////////////////////////////////////////////////////////////////
//! Get an attribute by its name or throw if not found.

AttributePtr Attributes::get(const tstring& strName) const
{
	AttributePtr pAttribute = find(strName);

	if (pAttribute.get() == nullptr)
		throw Core::InvalidArgException(Core::fmt(TXT("Failed to retrieve attribute '%s'"), strName.c_str()));

	return pAttribute;
}

//namespace XML
}
