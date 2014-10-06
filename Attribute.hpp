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
	Attribute(const tstring& name, const tstring& value);

	//
	// Properties.
	//

	//! Get the name.
	const tstring& name() const;

	//! Get the value.
	const tstring& value() const;

	//! Set the value.
	void setValue(const tstring& value);

private:
	//
	// Members.
	//
	tstring	m_name;			//!< The attribute name.
	tstring	m_value;		//!< The attribute value.
};

//! The default Attribute smart-pointer type.
typedef Core::SharedPtr<Attribute> AttributePtr;

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

inline Attribute::Attribute()
	: m_name(), m_value()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Construction from a name and value pair.

inline Attribute::Attribute(const tstring& name_, const tstring& value_)
	: m_name(name_), m_value(value_)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Get the name.

inline const tstring& Attribute::name() const
{
	return m_name;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the value.

inline const tstring& Attribute::value() const
{
	return m_value;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the value.

inline void Attribute::setValue(const tstring& value_)
{
	m_value = value_;
}

////////////////////////////////////////////////////////////////////////////////
//! Create an element with a specified name.

inline AttributePtr makeAttribute(const tstring& name, const tstring& value)
{
	return AttributePtr(new Attribute(name, value));
}

//namespace XML
}

#endif // XML_ATTRIBUTE_HPP
