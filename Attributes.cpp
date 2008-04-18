////////////////////////////////////////////////////////////////////////////////
//! \file   Attributes.cpp
//! \brief  The Attributes class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Attributes.hpp"
#include <Core/InvalidArgException.hpp>
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
		return (pAttribute->Name() == m_str);
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

void Attributes::Clear()
{
	m_vAttribs.clear();
}

////////////////////////////////////////////////////////////////////////////////
//! Set an attribute. If the attribute name already exists in the collection
//! it replaces it, otherwise it is appeneded.

void Attributes::SetAttribute(const AttributePtr& pAttribute)
{
	if (pAttribute->Name().empty())
		throw Core::InvalidArgException(TXT("Failed to set an attribute as the name is empty"));

	// Replace value or append attribute to collection.
	AttributePtr pExisting = Find(pAttribute->Name());

	if (pExisting.Get() != nullptr)
		pExisting->SetValue(pAttribute->Value());
	else
		m_vAttribs.push_back(pAttribute);
}

////////////////////////////////////////////////////////////////////////////////
//! Find an attribute by its name.

AttributePtr Attributes::Find(const tstring& strName) const
{
	AttributePtr pAttribute;

	Container::const_iterator it = std::find_if(m_vAttribs.begin(), m_vAttribs.end(), FindByName(strName));

	if (it != m_vAttribs.end())
		pAttribute = *it;

	return pAttribute;
}

//namespace XML
}
