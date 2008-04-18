////////////////////////////////////////////////////////////////////////////////
//! \file   CharTable.cpp
//! \brief  The CharTable class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "CharTable.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

CharTable::CharTable()
{
	STATIC_ASSERT(sizeof(uint) >= sizeof(tchar));

	// Set the whitespace chars.
	AppendFlags(TXT(' '),  WHITESPACE);
	AppendFlags(TXT('\t'), WHITESPACE);
	AppendFlags(TXT('\r'), WHITESPACE);
	AppendFlags(TXT('\n'), WHITESPACE);

	// Set the identifier chars.
	AppendFlags(TXT('A'), TXT('Z'), IDENTIFIER);
	AppendFlags(TXT('a'), TXT('z'), IDENTIFIER);
	AppendFlags(TXT('0'), TXT('9'), IDENTIFIER);
	AppendFlags(TXT('-'), IDENTIFIER);
	AppendFlags(TXT('_'), IDENTIFIER);
	AppendFlags(TXT('.'), IDENTIFIER);
	AppendFlags(TXT(':'), IDENTIFIER);
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

CharTable::~CharTable()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Get the flags for the character.

uint CharTable::GetFlags(uint nChar) const
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

uint& CharTable::GetFlags(uint nChar)
{
	// ASCII char?
	if (nChar < 128)
		return m_anASCII[nChar];

	return m_mapOther[nChar];
}

////////////////////////////////////////////////////////////////////////////////
//! Append flags for the character.

void CharTable::AppendFlags(tchar cChar, uint nFlags)
{
	GetFlags(cChar) |= nFlags;
}

////////////////////////////////////////////////////////////////////////////////
//! Append flags for the character range. The range is [First, Last] and hence
//! is inclusive of Last unlike with iterators.

void CharTable::AppendFlags(tchar cFirst, tchar cLast, uint nFlags)
{
	ASSERT(cLast >= cFirst);

	for (tchar cChar = cFirst; cChar <= cLast; ++cChar)
		GetFlags(cChar) |= nFlags;
}

//namespace XML
}
