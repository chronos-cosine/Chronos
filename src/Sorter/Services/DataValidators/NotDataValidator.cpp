/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NotDataValidator.cpp
 * Author: user
 * 
 * Created on 22 November 2018, 10:24 AM
 */

#include "Sorter/Services/DataValidators/NotDataValidator.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Models/Pattern.h"
#include "Sorter/Models/Result.h"
#include "Sorter/Models/BooleanOperator.h"

#include <iostream>
#include <map>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
            
            NotDataValidator::NotDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& data_context) 
                    : __data_context(data_context), 
                      __notifier(nullptr) {
            }
            
            NotDataValidator::NotDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& data_context,
                const std::shared_ptr<Notifier::INotifier>& notifier) 
                    : __data_context(data_context), 
                      __notifier(notifier) {
                notify("NotDataValidator::NotDataValidator()");
            }
                        
            void 
            NotDataValidator::notify(const std::string& message) {
                if (nullptr != __notifier) {
                    __notifier->notify(message);
                }
            }
        
            void 
            NotDataValidator::process(const std::shared_ptr<Sorter::Models::Job>& job) {
                notify("NotDataValidator::process()");
                
                for (auto& result: job->results) {
                    if (!result->passed) {
                        continue;
                    }
                    
                    for (auto& pair: result->pattern_matches) {
                        if (Sorter::Models::BooleanOperator::NOT 
                            == pair.first->boolean_operator) {
                            result->passed = false;
                        }
                        break;
                    }
                }
            }
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */