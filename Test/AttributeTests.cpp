////////////////////////////////////////////////////////////////////////////////
//! \file   AttributeTests.cpp
//! \brief  The unit tests for the Attribute struct.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/Attributes.hpp>

#ifdef __GNUG__
// base class 'X' has a non-virtual destructor
#pragma GCC diagnostic ignored "-Weffc++"
#endif

TEST_SET(Attribute)
{

TEST_CASE("default state is empty name and value")
{
	XML::Attribute attribute;

	TEST_TRUE(attribute.name() == TXT(""));
	TEST_TRUE(attribute.value() == TXT(""));
}
TEST_CASE_END

TEST_CASE("full construction specifies name and value")
{
	XML::Attribute attribute(TXT("name"), TXT("value"));

	TEST_TRUE(attribute.name() == TXT("name"));
	TEST_TRUE(attribute.value() == TXT("value"));
}
TEST_CASE_END

TEST_CASE("only the value can be modified after construction")
{
	XML::Attribute attribute(TXT("name"), TXT("value"));

	attribute.setValue(TXT("value2"));

	TEST_TRUE(attribute.value() == TXT("value2"));
}
TEST_CASE_END

TEST_CASE("a shared attribute can be constructed via a helper")
{
	XML::AttributePtr attribute = XML::makeAttribute(TXT("name"), TXT("value"));

	TEST_TRUE(attribute->name() == TXT("name"));
	TEST_TRUE(attribute->value() == TXT("value"));
}
TEST_CASE_END

}
TEST_SET_END
