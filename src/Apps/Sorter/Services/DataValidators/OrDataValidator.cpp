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

#include "Apps/Sorter/Services/DataValidators/OrDataValidator.h"
#include "Apps/Sorter/Models/Job.h"
#include "Apps/Sorter/Models/Pattern.h"
#include "Apps/Sorter/Models/Result.h"
#include "Apps/Sorter/Models/BooleanOperator.h"

#include <map>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
    
            OrDataValidator::OrDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& t_data_context) 
                    : m_data_context(t_data_context), 
                      Notifier::Notifiable() {
            }
            
            OrDataValidator::OrDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                const std::shared_ptr<Notifier::INotifier>& t_notifier) 
                    : m_data_context(t_data_context), 
                      Notifier::Notifiable(t_notifier) {
                notify("OrDataValidator::OrDataValidator()");
            }
            
            void 
            OrDataValidator::process(const std::shared_ptr<Sorter::Models::Job>& t_job) {
                notify("OrDataValidator::process()");
                
                for (auto& result: t_job->results) {
                    if (!result->passed) {
                        continue;
                    }
                    
                    if (m_data_context->bins[result->bin->id]->patterns.find(Sorter::Models::BooleanOperator::OR)
                        != m_data_context->bins[result->bin->id]->patterns.end()) {
                        result->passed = false;
                        for (auto& pair: result->pattern_matches) {
                            if (nullptr != pair.first) {
                                if (Sorter::Models::BooleanOperator::OR == pair.first->boolean_operator) {
                                    result->passed = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */
