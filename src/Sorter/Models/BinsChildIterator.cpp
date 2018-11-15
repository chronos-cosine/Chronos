/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinsIterator.cpp
 * Author: user
 * 
 * Created on 15 November 2018, 2:40 PM
 */

#include "Bin.h"
#include "BinsChildIterator.h"
#include "Bins.h"


namespace Sorter {
    namespace Models {
         
        BinsChildIterator::BinsChildIterator() 
            : __bins(nullptr) {
            
        }
        
        BinsChildIterator::BinsChildIterator(Bins* bins,
                              const unsigned long long& id)
            : __bins(bins) { 
            __iter = __bins->__children[id].begin();
        }
            
        BinsChildIterator& 
        BinsChildIterator::operator++() {
            if (__iter == __bins->__children[])
        }
        
        BinsChildIterator 
        BinsChildIterator::operator++(int) {
            
        }
        
        bool 
        BinsChildIterator::operator==(const BinsChildIterator& rhs) const {
            
        }
        
        bool 
        BinsChildIterator::operator!=(const BinsChildIterator& rhs) const {
            
        }
        
        Bin& 
        BinsChildIterator::operator*() const {
            
        }
        
        Bin& 
        BinsChildIterator::operator->() const {
            
        }
        
    } /* namespace Models */
} /* namespace Sorter */
