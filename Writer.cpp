////////////////////////////////////////////////////////////////////////////////
//! \file   Writer.cpp
//! \brief  The Writer class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Writer.hpp"
#include <Core/StringUtils.hpp>

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Writer::Writer()
	: m_flags(DEFAULT)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

Writer::Writer(uint flags)
	: m_flags(flags)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Writer::~Writer()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Write a document to a string buffer.

tstring Writer::formatDocument(DocumentPtr document)
{
	ASSERT(document.get() != nullptr);

	m_buffer.clear();

	writeContainer(*document.get());

	return m_buffer;
}

////////////////////////////////////////////////////////////////////////////////
//! Write a document to a string buffer.

tstring Writer::writeDocument(DocumentPtr document)
{
	XML::Writer writer;

	return writer.formatDocument(document);
}

////////////////////////////////////////////////////////////////////////////////
//! Write a container of nodes to the buffer.

void Writer::writeContainer(const NodeContainer& container)
{
	XML::NodeContainer::const_iterator it = container.beginChild();
	XML::NodeContainer::const_iterator end = container.endChild();

	for (; it != end; ++it)
	{
		XML::ElementNodePtr child = Core::dynamic_ptr_cast<XML::ElementNode>(*it);

		writeElement(child);
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Write the attributes to the buffer.

void Writer::writeAttributes(const Attributes& attributes)
{
	XML::Attributes::const_iterator it = attributes.begin();
	XML::Attributes::const_iterator end = attributes.end();

	for (; it != end; ++it)
	{
		m_buffer += Core::fmt(TXT(" %s=\"%s\""), (*it)->name().c_str(), (*it)->value().c_str());
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Write an element to the buffer.

void Writer::writeElement(ElementNodePtr element)
{
	if (element->hasChildren())
	{
		if (!element->getAttributes().isEmpty())
		{
			m_buffer += Core::fmt(TXT("<%s"), element->name().c_str());

			writeAttributes(element->getAttributes());

			m_buffer += TXT(">");
		}
		else
		{
			m_buffer += Core::fmt(TXT("<%s>"), element->name().c_str());
		}

		writeContainer(*element);

		m_buffer += Core::fmt(TXT("</%s>"), element->name().c_str());
	}
	else
	{
		if (!element->getAttributes().isEmpty())
		{
			m_buffer += Core::fmt(TXT("<%s"), element->name().c_str());

			writeAttributes(element->getAttributes());

			m_buffer += TXT("/>");
		}
		else
		{
			m_buffer += Core::fmt(TXT("<%s/>"), element->name().c_str());
		}
	}
}

//namespace XML
}
