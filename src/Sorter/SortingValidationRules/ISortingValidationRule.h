/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ISortingRule.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 1:50 PM
 */

#ifndef SORTER_ISORTINGVALIDATIONRULE_H
#define SORTER_ISORTINGVALIDATIONRULE_H

#include <map>
#include <set>

namespace Sorter {
    
    struct Pattern;
    struct Bin;
    
    namespace SortingValidationRules {
        
        class ISortingValidationRule {
            ISortingValidationRule(const ISortingValidationRule&) = delete;
            ISortingValidationRule& operator=(const ISortingValidationRule&) = delete;
        public:
            ~ISortingValidationRule() = default;
            ISortingValidationRule() = default;

            virtual void match() = 0;

        }; /* class ISortingRule */
        
    } /* namespace SortingValidationRules */
    
    
} /* namespace Sorter */

#endif /* SORTER_ISORTINGVALIDATIONRULE_H */

