////////////////////////////////////////////////////////////////////////////////
//! \file   TextNode.hpp
//! \brief  The TextNode class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_TEXTNODE_HPP
#define XML_TEXTNODE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Node.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The XML node type used for the text contained between other nodes.

class TextNode : public Node
{
public:
	//! Default constructor.
	TextNode();

	//! Construction from the text string.
	TextNode(const std::tstring& strText);
	
	//
	// Properties
	//

	//! Get the real type of the node.
	virtual NodeType Type() const;

	//! Get the text string.
	const std::tstring& Text() const;

	//! Set the text string.
	void SetText(const std::tstring& strText);

private:
	//
	// Members.
	//
	std::tstring	m_strText;		//!< The text string.

	//! Destructor.
	virtual ~TextNode();
};

//! The default TextNode smart-pointer type.
typedef Core::RefCntPtr<TextNode> TextNodePtr;

////////////////////////////////////////////////////////////////////////////////
//! Get the real type of the node.

inline NodeType TextNode::Type() const
{
	return TEXT_NODE;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the text string.

inline const std::tstring& TextNode::Text() const
{
	return m_strText;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the text string.

inline void TextNode::SetText(const std::tstring& strText)
{
	m_strText = strText;
}

//namespace XML
}

#endif // XML_TEXTNODE_HPP
