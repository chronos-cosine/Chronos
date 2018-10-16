/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeywordBooleanMatcher.h
 * Author: user
 *
 * Created on 16 October 2018, 11:23 AM
 */

#ifndef SORTER_KEYWORDBOOLEANMATCHER_H
#define SORTER_KEYWORDBOOLEANMATCHER_H

#include "Sorter/Bin.h"
#include "Sorter/Pattern.h"

#include <set>
#include <map>
#include <memory>

namespace Sorter {
    
    class KeywordBooleanMatcher {
    public:
        KeywordBooleanMatcher(); 
        virtual ~KeywordBooleanMatcher();
        void match_boolean(std::map<std::shared_ptr<Pattern>, std::set<unsigned long long>>& patterns,
                           std::set<std::shared_ptr<Bin>>& bins);
    };
}


#endif /* SORTER_KEYWORDBOOLEANMATCHER_H */

