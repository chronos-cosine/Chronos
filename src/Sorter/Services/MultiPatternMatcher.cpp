/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiPatternMatcher.cpp
 * Author: user
 * 
 * Created on 21 November 2018, 1:29 PM
 */

#include "MultiPatternMatcher.h"

namespace Sorter {
    namespace Services {
        
        MultiPatternMatcher::MultiPatternMatcher(
            const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& patterns) 
            : __matcher(patterns) {
        }
    
        void 
        MultiPatternMatcher::process(const std::shared_ptr<Sorter::Models::Job>& job) {
            
        }
          
    } /* namespace Services */
} /* namespace Sorter */ 