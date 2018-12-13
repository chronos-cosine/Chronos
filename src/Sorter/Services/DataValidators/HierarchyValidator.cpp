/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HierarchyValidator.cpp
 * Author: user
 * 
 * Created on 29 November 2018, 7:12 AM
 */

#include "Sorter/Services/DataValidators/HierarchyValidator.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Models/Pattern.h"
#include "Sorter/Models/Result.h"
#include "Sorter/Models/BooleanOperator.h"

#include <map>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
    
            HierarchyValidator::HierarchyValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& t_data_context) 
                    : m_data_context(t_data_context), 
                      Notifier::Notifiable() {
            }
            
            HierarchyValidator::HierarchyValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                const std::shared_ptr<Notifier::INotifier>& t_notifier) 
                    : m_data_context(t_data_context), 
                      Notifier::Notifiable(t_notifier) {
                notify("HierarchyValidator::HierarchyValidator()");
            }
            
            void 
            HierarchyValidator::process(const std::shared_ptr<Sorter::Models::Job>& t_job) {
                notify("HierarchyValidator::process()");
                
                for (auto& result: t_job->results) {
                    auto bin = result->bin;
                    
                    if (bin->is_root()) {
                        continue;
                    }
                    
                    do {
                        bin = m_data_context->bins[bin->parent_id.get()];
                        for (auto& check: t_job->results) {
                            if (check->bin == bin
                                && !check->passed) {
                                result->passed = false;
                                break;
                            }
                        }
                        
                        if (!result->passed) {
                            break;
                        }
                    } while (bin->parent_id.is_initialized());
                }
            }
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */