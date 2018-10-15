/* 
 * File:   RootNode.h
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_ROOTNODE_H
#define PATTERNMATCHER_ROOTNODE_H

#include "PatternMatcher/Node.h"

#include <memory>

namespace PatternMatcher
{
    template <typename PATTERN>
    class RootNode : public Node<PATTERN> {
    public:
        RootNode(RootNode&) = delete;
        RootNode& operator=(RootNode&) = delete;
    public:
        RootNode(); 
        virtual ~RootNode();

        virtual std::shared_ptr<Node<PATTERN>> g(const char& a); 
        
    }; /* class RootNode */
    
    template <typename PATTERN>
    RootNode<PATTERN>::RootNode()
            : Node<PATTERN>('~') {
        Node<PATTERN>::set_failure(std::shared_ptr<Node<PATTERN>>(this));
    }

    template <typename PATTERN>
    RootNode<PATTERN>::~RootNode() { }

    template <typename PATTERN>
    std::shared_ptr<Node<PATTERN>>
    RootNode<PATTERN>::g(const char& a) {
        std::shared_ptr<Node<PATTERN>> state = Node<PATTERN>::g(a);
        if (nullptr == state) {
            return std::shared_ptr<Node<PATTERN>>(this);
        }
        else {
            return state;
        }
    }

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_ROOTNODE_H */

