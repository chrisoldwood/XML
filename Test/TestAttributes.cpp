////////////////////////////////////////////////////////////////////////////////
//! \file   TestAttributes.cpp
//! \brief  The unit tests for the Attribute struct & Attributes class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/Attributes.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the Attribute struct & Attributes class.

void testAttributes()
{
	XML::Attribute oAttrib1;

	TEST_TRUE(oAttrib1.name() == TXT(""));
	TEST_TRUE(oAttrib1.value() == TXT(""));

	XML::Attribute oAttrib2(TXT("name"), TXT("value"));

	TEST_TRUE(oAttrib2.name() == TXT("name"));
	TEST_TRUE(oAttrib2.value() == TXT("value"));

	oAttrib2.setValue(TXT("value2"));

	TEST_TRUE(oAttrib2.value() == TXT("value2"));

	XML::Attributes oAttribs;

	TEST_TRUE(oAttribs.isEmpty() == true);
	TEST_TRUE(oAttribs.count() == 0);
	TEST_TRUE(oAttribs.begin() == oAttribs.end());

	XML::AttributePtr pAttrib = XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value")));

	oAttribs.setAttribute(pAttrib);

	XML::Attributes::iterator it = oAttribs.begin();

	TEST_TRUE((*it)->name() == TXT("name"));
	TEST_TRUE((*it)->value() == TXT("value"));

	(*it)->setValue(TXT("value2"));

	TEST_TRUE((*oAttribs.begin())->value() == TXT("value2"));

	oAttribs.setAttribute(XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value3"))));

	TEST_TRUE((*oAttribs.begin())->value() == TXT("value3"));

	pAttrib = oAttribs.find(TXT("name"));

	TEST_TRUE(pAttrib->name() == TXT("name"));
	TEST_TRUE(oAttribs.find(TXT("invalid_name")).get() == nullptr);

	pAttrib = oAttribs.get(TXT("name"));

	TEST_TRUE(pAttrib->name() == TXT("name"));
	TEST_THROWS(oAttribs.get(TXT("invalid_name")));
}
