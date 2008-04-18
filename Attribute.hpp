////////////////////////////////////////////////////////////////////////////////
//! \file   Attribute.hpp
//! \brief  The Attribute class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_ATTRIBUTE_HPP
#define XML_ATTRIBUTE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! An attribute. A collection cannot have duplicates so no write access to the
//! name is provided.

class Attribute
{
public:
	//! Default constructor.
	Attribute();

	//! Construction from a name and value pair.
	Attribute(const tstring& strName, const tstring& strValue);

	//
	// Properties.
	//

	//! Get the name.
	const tstring& Name() const;

	//! Get the value.
	const tstring& Value() const;

	//! Set the value.
	void SetValue(const tstring& strValue);

private:
	//
	// Members.
	//
	tstring	m_strName;		//!< The attribute name.
	tstring	m_strValue;		//!< The attribute value.
};

//! The default Attribute smart-pointer type.
typedef Core::SharedPtr<Attribute> AttributePtr;

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

inline Attribute::Attribute()
	: m_strName(), m_strValue()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a name and value pair.

inline Attribute::Attribute(const tstring& strName, const tstring& strValue)
	: m_strName(strName), m_strValue(strValue)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Get the name.

inline const tstring& Attribute::Name() const
{
	return m_strName;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the value.

inline const tstring& Attribute::Value() const
{
	return m_strValue;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the value.

inline void Attribute::SetValue(const tstring& strValue)
{
	m_strValue = strValue;
}

//namespace XML
}

#endif // XML_ATTRIBUTE_HPP
