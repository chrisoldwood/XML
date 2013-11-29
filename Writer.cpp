////////////////////////////////////////////////////////////////////////////////
//! \file   Writer.cpp
//! \brief  The Writer class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Writer.hpp"
#include <Core/StringUtils.hpp>

namespace XML
{

//! The default indentation style.
const tchar* Writer::DEFAULT_INDENT_STYLE = TXT("\t");

//! The default line terminator.
const tchar* Writer::DEFAULT_TERMINATOR = TXT("\n");
	
////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Writer::Writer()
	: m_flags(DEFAULT)
	, m_indentStyle(DEFAULT_INDENT_STYLE)
	, m_buffer()
	, m_depth(0)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Constructor.

Writer::Writer(uint flags, const tchar* indentStyle)
	: m_flags(flags)
	, m_indentStyle(indentStyle)
	, m_buffer()
	, m_depth(0)
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

	ASSERT(m_depth == 0);

	return m_buffer;
}

////////////////////////////////////////////////////////////////////////////////
//! Write a document to a string buffer.

tstring Writer::writeDocument(DocumentPtr document, uint flags, const tchar* indentStyle)
{
	XML::Writer writer(flags, indentStyle);

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
	tstring indentation;
	tstring terminator;

	if (!(m_flags & NO_FORMATTING))
	{
		for (uint i = 0; i != m_depth; ++i)
			indentation += m_indentStyle;

		terminator = DEFAULT_TERMINATOR;
	}

	if (element->hasChildren())
	{
		if (!element->getAttributes().isEmpty())
		{
			m_buffer += indentation;
			m_buffer += Core::fmt(TXT("<%s"), element->name().c_str());

			writeAttributes(element->getAttributes());

			m_buffer += TXT(">");
			m_buffer += terminator;
		}
		else
		{
			m_buffer += indentation;
			m_buffer += Core::fmt(TXT("<%s>"), element->name().c_str());
			m_buffer += terminator;
		}

		++m_depth;
		writeContainer(*element);
		--m_depth;

		m_buffer += indentation;
		m_buffer += Core::fmt(TXT("</%s>"), element->name().c_str());
		m_buffer += terminator;
	}
	else
	{
		if (!element->getAttributes().isEmpty())
		{
			m_buffer += indentation;
			m_buffer += Core::fmt(TXT("<%s"), element->name().c_str());

			writeAttributes(element->getAttributes());

			m_buffer += TXT("/>");
			m_buffer += terminator;
		}
		else
		{
			m_buffer += indentation;
			m_buffer += Core::fmt(TXT("<%s/>"), element->name().c_str());
			m_buffer += terminator;
		}
	}
}

//namespace XML
}
