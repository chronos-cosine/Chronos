/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinParentMatcher.h
 * Author: user
 *
 * Created on 16 October 2018, 9:51 AM
 */

#ifndef SORTER_BINPARENTMATCHER_H
#define SORTER_BINPARENTMATCHER_H

#include "Sorter/Bin.h"
#include <set>
#include <memory>

namespace Sorter {
    
    class BinParentMatcher {
    public:
        BinParentMatcher();
        virtual ~BinParentMatcher();
        void match_parents(std::set<std::shared_ptr<Bin>>& bins);
    };

} /* namespace Sorter */

#endif /* SORTER_BINPARENTMATCHER_H */

