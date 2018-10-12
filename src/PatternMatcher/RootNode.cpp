/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "RootNode.h"
#include "Node.h"

#include <memory>

namespace PatternMatcher
{

    RootNode::RootNode()
            : Node('~') {
        Node::set_failure(std::shared_ptr<Node>(this));
    }

    RootNode::~RootNode() { }

    std::shared_ptr<Node>
    RootNode::g(const char& a) {
        std::shared_ptr<Node> state = Node::g(a);
        if (nullptr == state) {
            return std::shared_ptr<Node>(this);
        }
        else {
            return state;
        }
    }

} /* namespace PatternMatcher */