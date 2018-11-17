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
        
        Bins::ForwardIterator::ForwardIterator(Sorter::Data::Bins& bins)
            : __iter(bins.__bins.begin()) {
            
        }
        
        Bins::ForwardIterator::ForwardIterator(const ForwardIterator& iter)
            : __iter(iter.__iter) {
            
        }
        
        Bins::ForwardIterator& 
        Bins::ForwardIterator::operator++() {
            ++__iter;
            return *this;
        }
        
        Bins::ForwardIterator
        Bins::ForwardIterator::operator++(int) {
            Bins::ForwardIterator temp(*this);
            operator++();
            return temp;
        }
                
        bool 
        Bins::ForwardIterator::operator==(const Bins::ForwardIterator& rhs) const {
            return __iter->first == rhs.__iter->first;
        }
                
        bool 
        Bins::ForwardIterator::operator!=(const Bins::ForwardIterator& rhs) const {
            return !(*this == rhs);
        }
                
        std::shared_ptr<Sorter::Models::Bin>
        Bins::ForwardIterator::operator*() {
            return __iter->second;
        }
                
        std::shared_ptr<Sorter::Models::Bin>
        Bins::ForwardIterator::operator->() {
            return __iter->second;
        }
        
        Bins::PatternIterator::PatternIterator(Sorter::Data::Bins& bins,
                                const std::shared_ptr<Sorter::Models::Bin>& bin,
                                const Sorter::Models::BooleanOperator& boolean_operator) {
            if (bins.__patterns.find(bin->id) == bins.__patterns.end()) {
                __iter = bins.__patterns.begin()->second.begin()->second.end();
            } else {
                __iter = bins.__patterns[bin->id][boolean_operator].begin();
            }
        }
        
        Bins::PatternIterator::PatternIterator(const PatternIterator& iter)
           : __iter(iter.__iter) {
        }
                
        Bins::PatternIterator& 
        Bins::PatternIterator::operator++() {
            ++__iter;
            return *this;
        }
        
        Bins::PatternIterator
        Bins::PatternIterator::operator++(int) {
            Bins::PatternIterator temp(*this);
            operator++();
            return temp;
        }
        
        bool 
        Bins::PatternIterator::operator==(const PatternIterator& rhs) const {
            return *__iter == *rhs.__iter;
        }
        
        bool 
        Bins::PatternIterator::operator!=(const PatternIterator& rhs) const {
            return !(*this == rhs);
        }
        
        std::shared_ptr<Sorter::Models::Pattern>
        Bins::PatternIterator::operator*() {
            return *__iter;
        }
        
        std::shared_ptr<Sorter::Models::Pattern>
        Bins::PatternIterator::operator->() {
            return *__iter;
        }
   
    } /* namespace Data */
} /* namespace Sorter */