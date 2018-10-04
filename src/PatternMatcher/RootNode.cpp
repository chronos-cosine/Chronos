/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "RootNode.h"
#include "Node.h"

namespace PatternMatcher
{

RootNode::RootNode()
    : Node('~')
{
    Node::set_failure(this);
}

RootNode::~RootNode() 
{ }

Node* 
RootNode::g(const char& a)
{
    Node* state = Node::g(a);
    if (nullptr == state)
    {
        return this;
    }
    else 
    {
        return state;
    }
}

} /* namespace PatternMatcher */