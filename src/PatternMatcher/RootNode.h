/* 
 * File:   RootNode.h
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_ROOTNODE_H
#define PATTERNMATCHER_ROOTNODE_H

#include "Node.h"

namespace PatternMatcher
{

    class RootNode : public Node
    {
    public:
        RootNode(); 
        virtual ~RootNode();

        virtual Node* g(const char& a); 
    }; /* class RootNode */

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_ROOTNODE_H */

