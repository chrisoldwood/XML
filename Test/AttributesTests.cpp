////////////////////////////////////////////////////////////////////////////////
//! \file   AttributesTests.cpp
//! \brief  The unit tests for the Attributes class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <XML/Attributes.hpp>

TEST_SET(Attributes)
{

TEST_CASE("default construction results in an empty sequence")
{
	XML::Attributes attributes;

	TEST_TRUE(attributes.isEmpty() == true);
	TEST_TRUE(attributes.count() == 0);
	TEST_TRUE(attributes.begin() == attributes.end());
}
TEST_CASE_END

TEST_CASE("setting an attribute adds it to the sequence if it doesn't already exist")
{
	XML::AttributePtr attribute = XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value")));

	XML::Attributes attributes;

	attributes.set(attribute);

	XML::Attributes::const_iterator it = attributes.begin();

	TEST_TRUE((*it)->name() == TXT("name"));
	TEST_TRUE((*it)->value() == TXT("value"));
}
TEST_CASE_END

TEST_CASE("setting an attribute replaces the existing attribute value if it already exists")
{
	XML::Attributes attributes;

	attributes.set(XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("original"))));
	attributes.set(XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("replacement"))));

	XML::Attributes::const_iterator it = attributes.begin();

	TEST_TRUE((*it)->value() == TXT("replacement"));
}
TEST_CASE_END

TEST_CASE("an attribute can be added from the name/value pair")
{
	XML::Attributes attributes;

	attributes.set(TXT("name"), TXT("value"));

	XML::Attributes::const_iterator it = attributes.begin();

	TEST_TRUE((*it)->name() == TXT("name"));
	TEST_TRUE((*it)->value() == TXT("value"));
}
TEST_CASE_END

TEST_CASE("an attribute can be replaced from a name/value pair")
{
	XML::Attributes attributes;

	attributes.set(TXT("name"), TXT("original"));
	attributes.set(TXT("name"), TXT("replacement"));

	XML::Attributes::const_iterator it = attributes.begin();

	TEST_TRUE((*it)->value() == TXT("replacement"));
}
TEST_CASE_END

TEST_CASE("attempting to add an unnamed attribute throws an exception")
{
	XML::Attributes attributes;

	XML::AttributePtr unnamedAttribute(new XML::Attribute);

	TEST_THROWS(attributes.set(unnamedAttribute));
}
TEST_CASE_END

TEST_CASE("modifying the value of an attribute modifies the sequence")
{
	XML::Attributes attributes;

	attributes.set(XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("original"))));

	XML::Attributes::iterator it = attributes.begin();

	(*it)->setValue(TXT("replacement"));

	it = attributes.begin();

	TEST_TRUE((*it)->value() == TXT("replacement"));
}
TEST_CASE_END

TEST_CASE("an attribute can be searched for by its name")
{
	XML::Attributes attributes;

	attributes.set(XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value"))));

	XML::AttributePtr attribute = attributes.find(TXT("name"));

	TEST_TRUE(attribute->name() == TXT("name"));
	TEST_TRUE(attribute->value() == TXT("value"));
}
TEST_CASE_END

TEST_CASE("searching for an invalid attribute returns a null pointer")
{
	XML::Attributes attributes;

	XML::AttributePtr attribute = attributes.find(TXT("invalid_name"));

	TEST_TRUE(attribute.get() == nullptr);
}
TEST_CASE_END

TEST_CASE("an attribute can be got by its name")
{
	XML::Attributes attributes;

	attributes.set(XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value"))));

	XML::AttributePtr attribute = attributes.get(TXT("name"));

	TEST_TRUE(attribute->name() == TXT("name"));
	TEST_TRUE(attribute->value() == TXT("value"));
}
TEST_CASE_END

TEST_CASE("an attribute value can be retrieved directly by its name")
{
	XML::Attributes attributes;

	attributes.set(XML::AttributePtr(new XML::Attribute(TXT("name"), TXT("value"))));

	TEST_TRUE(attributes.getValue(TXT("name")) == TXT("value"));
}
TEST_CASE_END

TEST_CASE("getting an invalid attribute throws an exception")
{
	XML::Attributes attributes;

	TEST_THROWS(attributes.get(TXT("invalid_name")));
}
TEST_CASE_END

TEST_CASE("getting the value for an invalid attribute throws an exception")
{
	XML::Attributes attributes;

	TEST_THROWS(attributes.getValue(TXT("invalid_name")));
}
TEST_CASE_END

TEST_CASE("clearing the attributes empties the sequence")
{
	XML::Attributes attributes;

	attributes.set(XML::AttributePtr(new XML::Attribute(TXT("name1"), TXT("value1"))));
	attributes.set(XML::AttributePtr(new XML::Attribute(TXT("name2"), TXT("value2"))));

	TEST_TRUE(attributes.count() != 0);

	attributes.clear();

	TEST_TRUE(attributes.count() == 0);
}
TEST_CASE_END

}
TEST_SET_END
