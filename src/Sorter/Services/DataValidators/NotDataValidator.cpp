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

#include <map>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
            
            NotDataValidator::NotDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& t_data_context) 
                    : m_data_context(t_data_context), 
                      m_notifier(nullptr) {
            }
            
            NotDataValidator::NotDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                const std::shared_ptr<Notifier::INotifier>& t_notifier) 
                    : m_data_context(t_data_context), 
                      m_notifier(t_notifier) {
                notify("NotDataValidator::NotDataValidator()");
            }
                        
            void 
            NotDataValidator::notify(const std::string& t_message) {
                if (nullptr != m_notifier) {
                    m_notifier->notify(t_message);
                }
            }
        
            void 
            NotDataValidator::process(const std::shared_ptr<Sorter::Models::Job>& t_job) {
                notify("NotDataValidator::process()");
                
                for (auto& result: t_job->results) {
                    std::cout << "NotDataValidator::testing " << result->bin->name << std::endl;
                    
                    if (!result->passed) {
                        continue;
                    }
                    
                    for (auto& pair: result->pattern_matches) {
                        if (nullptr != pair.first 
                            && Sorter::Models::BooleanOperator::NOT == pair.first->boolean_operator) {
                            result->passed = false;
                        }
                        break;
                    }
                }
            }
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */