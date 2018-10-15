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

        virtual Node<PATTERN>* g(const char& a); 
        
    }; /* class RootNode */
    
    template <typename PATTERN>
    RootNode<PATTERN>::RootNode()
            : Node<PATTERN>('~') {
        Node<PATTERN>::set_failure(this);
    }

    template <typename PATTERN>
    RootNode<PATTERN>::~RootNode() { }

    template <typename PATTERN>
    Node<PATTERN>*
    RootNode<PATTERN>::g(const char& a) {
        Node<PATTERN>* state = Node<PATTERN>::g(a);
        if (nullptr == state) {
            return this;
        }
        else {
            return state;
        }
    }

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_ROOTNODE_H */

