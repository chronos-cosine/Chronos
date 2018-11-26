/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OrDataValidator.cpp
 * Author: user
 * 
 * Created on 22 November 2018, 10:25 AM
 */

#include "OrDataValidator.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Models/Pattern.h"
#include "Sorter/Models/Result.h"
#include "Sorter/Models/BooleanOperator.h"

#include <iostream>
#include <map>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
    
            OrDataValidator::OrDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& data_context) 
                    : __data_context(data_context) {
                std::cout << "OrDataValidator::OrDataValidator()"<< std::endl;
                
            }
        
            void 
            OrDataValidator::process(const std::shared_ptr<Sorter::Models::Job>& job) {
                std::cout << "OrDataValidator::process()"<< std::endl;
                for (auto& result: job->results) {
                    if (!result->passed) {
                        continue;
                    }
                    
                    if (__data_context->bins[result->bin->id]->patterns.find(Sorter::Models::BooleanOperator::OR)
                        != __data_context->bins[result->bin->id]->patterns.end()) {
                        for (auto& pair: result->pattern_matches) {
                            if (Sorter::Models::BooleanOperator::OR 
                                == pair.first->boolean_operator) {
                                result->passed = false;
                            }
                            break;
                        }
                    }
                }
            }
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */
