/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bins.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 16 November 2018, 8:51 PM
 */

#include <memory>

#include "Bins.h"


namespace Sorter {
    namespace Data {
        
        Bins::PatternIterator 
        Bins::patterns(const std::shared_ptr<Sorter::Models::Bin>& bin, 
                            const Sorter::Models::BooleanOperator& boolean_operator) {
            return Bins::PatternIterator(*this, bin, boolean_operator);
        }
        
        Bins::PatternIterator 
        Bins::patterns_end() {
            return Bins::PatternIterator();
        }
        
        Bins::ForwardIterator 
        Bins::begin() {
            return Bins::ForwardIterator(*this);
        }
        
        Bins::ForwardIterator 
        Bins::end() {
            return Bins::ForwardIterator();
        }
        
        void 
        Bins::add(const std::shared_ptr<Sorter::Models::Bin>& bin) {
            __bins[bin->id] = bin;
        }
        
        void 
        Bins::add(const std::shared_ptr<Sorter::Models::Pattern>& pattern) {
            __patterns[pattern->bin_id][pattern->boolean_operator].insert(pattern);
        }
   
    } /* namespace Data */
} /* namespace Sorter */