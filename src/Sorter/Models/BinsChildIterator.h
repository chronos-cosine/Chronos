/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinsIterator.h
 * Author: user
 *
 * Created on 15 November 2018, 2:40 PM
 */

#ifndef SORTER_MODELS_BINSITERATOR_H
#define SORTER_MODELS_BINSITERATOR_H

#include <set>

namespace Sorter {
    namespace Models {
        
        class BinsChildIterator {
        public:
            virtual ~BinsChildIterator() = default;
            BinsChildIterator();
            BinsChildIterator(Bins* bins,
                              const unsigned long long& id);
            
            BinsChildIterator& operator++();
            BinsChildIterator operator++(int);
            bool operator==(const BinsChildIterator& rhs) const;
            bool operator!=(const BinsChildIterator& rhs) const;
            Bin& operator*() const;
            Bin& operator->() const;
        private:
            Bins* __bins;
            std::set<unsigned long long>::const_iterator __current;
            std::set<unsigned long long>::const_iterator __end;
        };
        
    } /* namespace Models */
} /* namespace Sorter */

#endif /* SORTER_MODELS_BINSITERATOR_H */

