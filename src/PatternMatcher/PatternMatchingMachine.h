/* 
 * File:   PatternMatchingMachine.h
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_PATTERNMATCHINGMACHINE_H
#define PATTERNMATCHER_PATTERNMATCHINGMACHINE_H

#include <boost/signals2.hpp>
#include <set>

#include "IPattern.h"
#include "Node.h"

namespace PatternMatcher
{
 
    class PatternMatchingMachine { 
    public:
        PatternMatchingMachine(const std::set<IPattern*>& patterns); 
        virtual ~PatternMatchingMachine(); 
 
        void match(IPattern* input, void* sender) const; 

        boost::signals2::signal<
            void(void* /* sender */, 
                 const unsigned long long& /* total_matches */,
                 PatternMatcher::IPattern* /* input */)>& completed();
        boost::signals2::signal<
            void(void* /* sender */, 
                 const unsigned long long& /* position */,
                 PatternMatcher::IPattern* /* input */,
                 const std::set<PatternMatcher::IPattern*>& /* patterns */)>& match_found();
    private:
        Node* __root;
        boost::signals2::signal<
            void(void*, 
                 const unsigned long long&,
                 IPattern*)> __completed;
        boost::signals2::signal<
            void(void*, 
                 const unsigned long long&,
                 IPattern*,
                 const std::set<IPattern*>&)> __match_found;

        void enter(IPattern* pattern);
        void construct_goto_function(const std::set<IPattern*>& patterns);
        void construct_failure_function();
    }; /* class PatternMatchingMachine */

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_PATTERNMATCHINGMACHINE_H */

