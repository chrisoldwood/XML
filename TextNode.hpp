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
	TextNode(const tstring& strText);
	
	//
	// Properties
	//

	//! Get the real type of the node.
	virtual NodeType type() const;

	//! Get the text string.
	const tstring& text() const;

	//! Set the text string.
	void setText(const tstring& strText);

private:
	//
	// Members.
	//
	tstring	m_strText;		//!< The text string.

	//! Destructor.
	virtual ~TextNode();
};

//! The default TextNode smart-pointer type.
typedef Core::RefCntPtr<TextNode> TextNodePtr;

////////////////////////////////////////////////////////////////////////////////
//! Get the real type of the node.

inline NodeType TextNode::type() const
{
	return TEXT_NODE;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the text string.

inline const tstring& TextNode::text() const
{
	return m_strText;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the text string.

inline void TextNode::setText(const tstring& strText)
{
	m_strText = strText;
}

//namespace XML
}

#endif // XML_TEXTNODE_HPP
