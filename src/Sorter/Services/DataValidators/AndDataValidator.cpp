/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AndDataValidator.cpp
 * Author: user
 * 
 * Created on 22 November 2018, 10:25 AM
 */

#include "Sorter/Services/DataValidators/AndDataValidator.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Models/Pattern.h"
#include "Sorter/Models/Result.h"
#include "Sorter/Models/BooleanOperator.h"

#include <iostream>
#include <map>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
            
            AndDataValidator::AndDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& data_context) 
                    : __data_context(data_context), 
                      __notifier(nullptr) {
            }
            
            AndDataValidator::AndDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& data_context,
                const std::shared_ptr<Notifier::INotifier>& notifier) 
                    : __data_context(data_context), 
                      __notifier(notifier) {
                notify("AndDataValidator::AndDataValidator()");
            }
            
            void 
            AndDataValidator::notify(const std::string& message) {
                if (nullptr != __notifier) {
                    __notifier->notify(message);
                }
            }
    
            void 
            AndDataValidator::process(const std::shared_ptr<Sorter::Models::Job>& job) {
                notify("AndDataValidator::process()");
                
                for (auto& result: job->results) {
                    if (!result->passed) {
                        continue;
                    }
                    
                    for (auto& pattern: __data_context->bins[result->bin->id]
                                        ->patterns[Sorter::Models::BooleanOperator::AND]) {
                        if (result->pattern_matches.find(pattern)
                            == result->pattern_matches.end()) {
                            result->passed = false;
                            break;
                        }
                    }
                }
            }
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */
