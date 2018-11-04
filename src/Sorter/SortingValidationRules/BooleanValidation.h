/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BooleanMatch.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 1:59 PM
 */

#ifndef SORTER_SORTINGRULES_BOOLEANVALIDATION_H
#define SORTER_SORTINGRULES_BOOLEANVALIDATION_H

#include "ISortingValidationRule.h"

#include <map>
#include <set>

namespace Sorter {
    
    class Bin;
    class Pattern;
    
    namespace SortingValidationRules {
        
        class BooleanValidation : public ISortingValidationRule {
            BooleanValidation() = delete;
            BooleanValidation(const BooleanValidation&) = delete;
            BooleanValidation& operator=(const BooleanValidation&) = delete;
        public:
            virtual ~BooleanValidation() = default;
        
            virtual void match();
        private:
            
        }; /* class BooleanValidation */
        
    } /* namespace SortingValidationRules */
    
} /* namespace Sorter */

#endif /* SORTER_SORTINGRULES_BOOLEANVALIDATION_H */

