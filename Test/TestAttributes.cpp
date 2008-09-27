////////////////////////////////////////////////////////////////////////////////
//! \file   TestAttributes.cpp
//! \brief  The unit tests for the Attribute struct & Attributes class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/Attributes.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the Attribute struct & Attributes class.

void TestAttributes()
{
	XML::Attribute oAttrib1;

	TEST_TRUE(oAttrib1.Name() == TXT(""));
	TEST_TRUE(oAttrib1.Value() == TXT(""));

	XML::Attribute oAttrib2(TXT("name"), TXT("value"));

	TEST_TRUE(oAttrib2.Name() == TXT("name"));
	TEST_TRUE(oAttrib2.Value() == TXT("value"));

	oAttrib2.SetValue(TXT("value2"));

	TEST_TRUE(oAttrib2.Value() == TXT("value2"));

	XML::Attributes oAttribs;

	TEST_TRUE(oAttribs.IsEmpty() == true);
	TEST_TRUE(oAttribs.Count() == 0);
	TEST_TRUE(oAttribs.Begin() == oAttribs.End());

	XML::AttributePtr pAttrib = XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value")));

	oAttribs.SetAttribute(pAttrib);

	XML::Attributes::iterator it = oAttribs.Begin();

	TEST_TRUE((*it)->Name() == TXT("name"));
	TEST_TRUE((*it)->Value() == TXT("value"));

	(*it)->SetValue(TXT("value2"));

	TEST_TRUE((*oAttribs.Begin())->Value() == TXT("value2"));

	oAttribs.SetAttribute(XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value3"))));

	TEST_TRUE((*oAttribs.Begin())->Value() == TXT("value3"));

	pAttrib = oAttribs.Find(TXT("name"));

	TEST_TRUE(pAttrib->Name() == TXT("name"));
	TEST_TRUE(oAttribs.Find(TXT("invalid_name")).Get() == nullptr);

	pAttrib = oAttribs.Get(TXT("name"));

	TEST_TRUE(pAttrib->Name() == TXT("name"));
	TEST_THROWS(oAttribs.Get(TXT("invalid_name")));
}
