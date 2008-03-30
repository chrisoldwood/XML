////////////////////////////////////////////////////////////////////////////////
//! \file   CommentNode.hpp
//! \brief  The CommentNode class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef XML_COMMENTNODE_HPP
#define XML_COMMENTNODE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Node.hpp"

namespace XML
{

////////////////////////////////////////////////////////////////////////////////
//! The XML node type used to for a comment.

class CommentNode : public Node
{
public:
	//! Default constructor.
	CommentNode();

	//! Construction from a string comment.
	CommentNode(const std::tstring& strComment);

	//
	// Properties
	//

	//! Get the real type of the node.
	virtual NodeType Type() const;

	//! Get the comment.
	const std::tstring& Comment() const;

	//! Set the comment.
	void SetComment(const std::tstring& strComment);

private:
	//
	// Members.
	//
	std::tstring	m_strComment;		//!< The string comment.

	//! Destructor.
	virtual ~CommentNode();
};

//! The default CommentNode smart-pointer type.
typedef Core::RefCntPtr<CommentNode> CommentNodePtr;

////////////////////////////////////////////////////////////////////////////////
//! Get the real type of the node.

inline NodeType CommentNode::Type() const
{
	return COMMENT_NODE;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the comment.

inline const std::tstring& CommentNode::Comment() const
{
	return m_strComment;
}

////////////////////////////////////////////////////////////////////////////////
//! Set the comment.

inline void CommentNode::SetComment(const std::tstring& strComment)
{
	m_strComment = strComment;
}

//namespace XML
}

#endif // XML_COMMENTNODE_HPP
