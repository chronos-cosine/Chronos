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
        
            template <typename T>
            class ForwardIterator : public std::iterator<std::input_iterator_tag, T> {
            public:
                ForwardIterator(const std::shared_ptr<Sorter::Data::Bins>& bins);
                ForwardIterator(const ForwardIterator& iter);
                
                ForwardIterator& operator++();
                ForwardIterator operator++(int);
                bool operator==(const ForwardIterator& rhs) const;
                bool operator!=(const ForwardIterator& rhs) const;
                T& operator*() const;
                T& operator->() const;
            private:
                std::map<unsigned long long, std::shared_ptr<Sorter::Models::Bin>>::iterator __iter;
            }; /*  class ForwardIterator */
            
            template <typename T>
            class PatternIterator : public std::iterator<std::input_iterator_tag, T> {
            public:
                PatternIterator(const std::shared_ptr<Sorter::Data::Bins>& bins, 
                                const Sorter::Models::BooleanOperator& boolean_operator);
                PatternIterator(const PatternIterator& iter);
                
                PatternIterator& operator++();
                PatternIterator operator++(int);
                bool operator==(const PatternIterator& rhs) const;
                bool operator!=(const PatternIterator& rhs) const;
                T& operator*() const;
                T& operator->() const;
            private:  
                std::set<std::shared_ptr<Sorter::Models::Pattern>>::iterator __iter;
            }; /* class PatternIterator */
            
        public:
            typedef ForwardIterator<Sorter::Models::Bin> iterator;
            typedef ForwardIterator<const Sorter::Models::Bin> const_iterator;
            typedef PatternIterator<Sorter::Models::Pattern> pattern_iterator;
            typedef PatternIterator<const Sorter::Models::Pattern> const_pattern_iterator;
            
            pattern_iterator patterns(const std::shared_ptr<Sorter::Data::Bins>& bins, 
                                const Sorter::Models::BooleanOperator& boolean_operator);
            pattern_iterator patterns_end();
            const_pattern_iterator patterns(const std::shared_ptr<Sorter::Data::Bins>& bins, 
                                const Sorter::Models::BooleanOperator& boolean_operator) const;
            const_pattern_iterator patterns_end() const;
            
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;
        private:
            std::map<unsigned long long, std::shared_ptr<Sorter::Models::Bin>> __bins;
            std::map<unsigned long long, std::map<Sorter::Models::BooleanOperator,
                        std::set<std::shared_ptr<Sorter::Models::Pattern>>>> __patterns;
            
        }; /* class Bins */
        
        template <typename T>
        Bins::ForwardIterator<T>::ForwardIterator(const std::shared_ptr<Sorter::Data::Bins>& bins)
            : __iter(bins->__bins.begin()) {
            
        }
        
        template <typename T>
        Bins::ForwardIterator<T>::ForwardIterator(const ForwardIterator& iter)
            : __iter(iter.__iter) {
            
        }
        
        template <typename T>
        Bins::ForwardIterator<T>& 
        Bins::ForwardIterator<T>::operator++() {
            ++__iter;
            return *this;
        }
        
        template <typename T>
        Bins::ForwardIterator<T>
        Bins::ForwardIterator<T>::operator++(int) {
            Bins::ForwardIterator<T> temp(*this);
            operator++();
            return temp;
        }
                
        template <typename T>
        bool 
        Bins::ForwardIterator<T>::operator==(const Bins::ForwardIterator<T>& rhs) const {
            return __iter->first == rhs.__iter->first;
        }
                
        template <typename T>
        bool 
        Bins::ForwardIterator<T>::operator!=(const Bins::ForwardIterator<T>& rhs) const {
            return !(*this == rhs);
        }
                
        template <typename T>
        T& 
        Bins::ForwardIterator<T>::operator*() const {
            return *__iter->second;
        }
                
        template <typename T>
        T& 
        Bins::ForwardIterator<T>::operator->() const {
            return *__iter->second;
        }
        
        template <typename T>
        Bins::PatternIterator<T>::PatternIterator(const std::shared_ptr<Sorter::Data::Bins>& bins, 
                        const Sorter::Models::BooleanOperator& boolean_operator) {
            if (bins->__patterns.find(boolean_operator) == bins->__patterns.end()) {
                __iter = bins->__patterns.end();
            } else {
                __iter = bins->__patterns[boolean_operator].begin();
            }
        }
        
        template <typename T>
        Bins::PatternIterator<T>::PatternIterator(const PatternIterator& iter)
           : __iter(iter.__iter) {
        }
                
        template <typename T>
        Bins::PatternIterator<T>& 
        Bins::PatternIterator<T>::operator++() {
            ++__iter;
            return *this;
        }
        
        template <typename T>
        Bins::PatternIterator<T> 
        Bins::PatternIterator<T>::operator++(int) {
            Bins::PatternIterator<T> temp(*this);
            operator++();
            return temp;
        }
        
        template <typename T>
        bool 
        Bins::PatternIterator<T>::operator==(const PatternIterator& rhs) const {
            return *__iter == *rhs.__iter;
        }
        
        template <typename T>
        bool 
        Bins::PatternIterator<T>::operator!=(const PatternIterator& rhs) const {
            return !(*this == rhs);
        }
        
        template <typename T>
        T& 
        Bins::PatternIterator<T>::operator*() const {
            return *__iter;
        }
        
        template <typename T>
        T& 
        Bins::PatternIterator<T>::operator->() const {
            return *__iter;
        }
                
    } /* namespace Data */
} /* namespace Sorter */

#endif /* SORTER_DATA_BINS_H */
