/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bins.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 16 November 2018, 8:51 PM
 */

#ifndef SORTER_DATA_BINS_H
#define SORTER_DATA_BINS_H

#include "Sorter/Models/Bin.h"
#include "Sorter/Models/BooleanOperator.h"
#include "Sorter/Models/Pattern.h"

#include <functional>
#include <map>
#include <memory>
#include <set>

namespace Sorter {
    namespace Data {
        
        class Bins {
            Bins(const Bins&) = delete;
            Bins& operator=(const Bins&) = delete;
        
            class ForwardIterator : public std::iterator<std::input_iterator_tag, Sorter::Models::Bin> {
            public:
                ForwardIterator(Sorter::Data::Bins& bins);
                ForwardIterator(const ForwardIterator& iter);
                ForwardIterator() = default;
                
                ForwardIterator& operator++();
                ForwardIterator operator++(int);
                bool operator==(const ForwardIterator& rhs) const;
                bool operator!=(const ForwardIterator& rhs) const;
                std::shared_ptr<Sorter::Models::Bin>& operator*();
                std::shared_ptr<Sorter::Models::Bin>& operator->();
            private:
                std::map<unsigned long long, std::shared_ptr<Sorter::Models::Bin>>::iterator __iter;
            }; /*  class ForwardIterator */
            
            class PatternIterator : public std::iterator<std::input_iterator_tag, Sorter::Models::Pattern> {
            public:
                PatternIterator(Sorter::Data::Bins& bins,
                                const std::shared_ptr<Sorter::Models::Bin>& bin,
                                const Sorter::Models::BooleanOperator& boolean_operator);
                PatternIterator(const PatternIterator& iter);
                PatternIterator() = default;
                
                PatternIterator& operator++();
                PatternIterator operator++(int);
                bool operator==(const PatternIterator& rhs) const;
                bool operator!=(const PatternIterator& rhs) const;
                std::shared_ptr<Sorter::Models::Pattern>& operator*();
                std::shared_ptr<Sorter::Models::Pattern>& operator->();
            private:  
                std::set<std::shared_ptr<Sorter::Models::Pattern>>::iterator __iter;
            }; /* class PatternIterator */
            
        public:
            PatternIterator patterns(const std::shared_ptr<Sorter::Models::Bin>& bin, 
                                const Sorter::Models::BooleanOperator& boolean_operator);
            PatternIterator patterns_end();
            
            ForwardIterator begin();
            ForwardIterator end();
            void add(const std::shared_ptr<Sorter::Models::Bin>& bin);
            void add(const std::shared_ptr<Sorter::Models::Pattern>& pattern);
        private:
            std::map<unsigned long long, std::shared_ptr<Sorter::Models::Bin>> __bins;
            std::map<unsigned long long, std::map<Sorter::Models::BooleanOperator,
                        std::set<std::shared_ptr<Sorter::Models::Pattern>>>> __patterns;
            
        }; /* class Bins */
        
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
                
        std::shared_ptr<Sorter::Models::Bin>& 
        Bins::ForwardIterator::operator*() {
            return __iter->second;
        }
                
        std::shared_ptr<Sorter::Models::Bin>& 
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
        
        std::shared_ptr<Sorter::Models::Pattern>& 
        Bins::PatternIterator::operator*() {
            return *__iter;
        }
        
        std::shared_ptr<Sorter::Models::Pattern>& 
        Bins::PatternIterator::operator->() {
            return *__iter;
        }
                
    } /* namespace Data */
} /* namespace Sorter */

#endif /* SORTER_DATA_BINS_H */
