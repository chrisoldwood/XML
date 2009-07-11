////////////////////////////////////////////////////////////////////////////////
//! \file   CharTable.hpp
//! \brief  The CharTable class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_CHARTABLE_HPP
#define XML_CHARTABLE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <map>

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! A lookup table used to check the attributes of characters in an XML stream.
//! The class optimises for the ASCII character range by using a fixed size
//! array, and then falls back to a map for non-ASCII chars.

class CharTable
{
public:
	//! Default constructor.
	CharTable();

	//! Destructor.
	~CharTable();
	
	//
	// Methods.
	//

	//! Check if a character is whitespace. 
	bool isWhitespace(tchar cChar) const;

	//! Check if a character is valid in an identifier.
	bool isIdentifier(tchar cChar) const;

private:
	//! A map of character to flags.
	typedef std::map<uint, uint> MapCharFlags;

	//! The size of the ASCII table.
	static const size_t TABLE_SIZE = 127;

	//
	// Members.
	//
	uint			m_anASCII[TABLE_SIZE];	//!< Lookup table for the ASCII chars.
	MapCharFlags	m_mapOther;				//!< Lookup map for non-ASCII chars.

	//! The character flags
	enum
	{
		DEFAULT		= 0x0000,		//!< The default flags.
		WHITESPACE	= 0x0001,		//!< A whitespace character.
		IDENTIFIER	= 0x0002,		//!< A character for use in identifiers.
	};

	//
	// Internal methods.
	//

	//! Get the flags for the character.
	uint getFlags(uint nChar) const;

	//! Get the flags for the character.
	uint& getFlags(uint nChar);

	//! Append flags for the character.
	void appendFlags(tchar cChar, uint nFlags);

	//! Append flags for the character range.
	void appendFlags(tchar cFirst, tchar cLast, uint nFlags);
};

////////////////////////////////////////////////////////////////////////////////
//! Check if a character is whitespace. 

inline bool CharTable::isWhitespace(tchar cChar) const
{
	return (getFlags(cChar) & WHITESPACE);
}

////////////////////////////////////////////////////////////////////////////////
//! Check if a character is valid in an identifier.

inline bool CharTable::isIdentifier(tchar cChar) const
{
	return (getFlags(cChar) & IDENTIFIER);
}

//namespace XML
}

#endif // XML_CHARTABLE_HPP
