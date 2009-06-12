////////////////////////////////////////////////////////////////////////////////
//! \file   IOException.hpp
//! \brief  The IOException class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_IOEXCEPTION_HPP
#define XML_IOEXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <Core/Exception.hpp>

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The type of exception throw during serialization of an XML document.

class IOException : public Core::Exception
{
public:
	//! Construction from a string containing the details.
	IOException(const tstring& strDetails);

	//! Destructor.
	virtual ~IOException() throw();
};

////////////////////////////////////////////////////////////////////////////////
//! Construction from a string containing the details.

inline IOException::IOException(const tstring& strDetails)
	: Exception(strDetails)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

inline IOException::~IOException() throw()
{
}

//namespace XML
}

#endif // XML_IOEXCEPTION_HPP
