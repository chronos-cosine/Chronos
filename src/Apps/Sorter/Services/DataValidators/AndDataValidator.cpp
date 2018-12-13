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

#include "Apps/Sorter/Services/DataValidators/AndDataValidator.h"
#include "Apps/Sorter/Models/Job.h"
#include "Apps/Sorter/Models/Pattern.h"
#include "Apps/Sorter/Models/Result.h"
#include "Apps/Sorter/Models/BooleanOperator.h"

#include <map>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
            
            AndDataValidator::AndDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& t_data_context) 
                    : m_data_context(t_data_context), 
                      Notifier::Notifiable() {
            }
            
            AndDataValidator::AndDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                const std::shared_ptr<Notifier::INotifier>& t_notifier) 
                    : m_data_context(t_data_context), 
                      Notifier::Notifiable(t_notifier) {
                notify("AndDataValidator::AndDataValidator()");
            }
            
            void 
            AndDataValidator::process(const std::shared_ptr<Sorter::Models::Job>& t_job) {
                notify("AndDataValidator::process()");
                
                for (auto& result: t_job->results) {
                    if (!result->passed) {
                        continue;
                    }
                    
                    for (auto& pattern: m_data_context->bins[result->bin->id]->patterns[Sorter::Models::BooleanOperator::AND]) {
                        if (result->pattern_matches.find(pattern) == result->pattern_matches.end()) {
                            result->passed = false;
                            break;
                        }
                    }
                }
            }
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */
