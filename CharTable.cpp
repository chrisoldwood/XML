////////////////////////////////////////////////////////////////////////////////
//! \file   CharTable.cpp
//! \brief  The CharTable class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "CharTable.hpp"

#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2)) // GCC 4.2+
// Caused by the STATIC_ASSERT macro.
#pragma GCC diagnostic ignored "-Wunused-value"
#endif

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

CharTable::CharTable()
{
	STATIC_ASSERT(sizeof(uint) >= sizeof(tchar));

	std::fill(m_anASCII, m_anASCII+TABLE_SIZE, 0);

	// Set the whitespace chars.
	appendFlags(TXT(' '),  WHITESPACE);
	appendFlags(TXT('\t'), WHITESPACE);
	appendFlags(TXT('\r'), WHITESPACE);
	appendFlags(TXT('\n'), WHITESPACE);

	// Set the identifier chars.
	appendFlags(TXT('A'), TXT('Z'), IDENTIFIER);
	appendFlags(TXT('a'), TXT('z'), IDENTIFIER);
	appendFlags(TXT('0'), TXT('9'), IDENTIFIER);
	appendFlags(TXT('-'), IDENTIFIER);
	appendFlags(TXT('_'), IDENTIFIER);
	appendFlags(TXT('.'), IDENTIFIER);
	appendFlags(TXT(':'), IDENTIFIER);
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

CharTable::~CharTable()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Get the flags for the character.

uint CharTable::getFlags(uint nChar) const
{
	// ASCII char?
	if (nChar < 128)
		return m_anASCII[nChar];

	// Non-ASCII non-default?
	MapCharFlags::const_iterator it = m_mapOther.find(nChar);

	if (it != m_mapOther.end())
		return it->second;

	return DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the flags for the character.
//  NB: The use of map<T>::operator[] assumes that the default value == T().

uint& CharTable::getFlags(uint nChar)
{
	// ASCII char?
	if (nChar < 128)
		return m_anASCII[nChar];

	return m_mapOther[nChar];
}

////////////////////////////////////////////////////////////////////////////////
//! Append flags for the character.

void CharTable::appendFlags(tchar cChar, uint nFlags)
{
	getFlags(cChar) |= nFlags;
}

////////////////////////////////////////////////////////////////////////////////
//! Append flags for the character range. The range is [First, Last] and hence
//! is inclusive of Last unlike with iterators.

void CharTable::appendFlags(tchar cFirst, tchar cLast, uint nFlags)
{
	ASSERT(cLast >= cFirst);

	for (tchar cChar = cFirst; cChar <= cLast; ++cChar)
		getFlags(cChar) |= nFlags;
}

//namespace XML
}
