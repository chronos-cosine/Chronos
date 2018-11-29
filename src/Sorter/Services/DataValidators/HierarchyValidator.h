/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HierarchyValidator.h
 * Author: user
 *
 * Created on 29 November 2018, 7:12 AM
 */

#ifndef SORTER_SERVICES_DATAVALIDATORS_HIERARCHYVALIDATOR_H
#define SORTER_SERVICES_DATAVALIDATORS_HIERARCHYVALIDATOR_H

#include "Notifier/INotifier.h"
#include "Sorter/Data/DataContext.h"
#include "Sorter/Services/IDataValidator.h"

#include <memory>
#include <string>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
    
            class HierarchyValidator : public IDataValidator {
            public:
                virtual ~HierarchyValidator() = default;
                HierarchyValidator(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                           const std::shared_ptr<Notifier::INotifier>& t_notifier);
                HierarchyValidator(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context);

                virtual void process(const std::shared_ptr<Sorter::Models::Job>& t_job);
            private:
                void notify(const std::string& t_message);
            private:
                std::shared_ptr<Sorter::Data::DataContext> m_data_context;
                std::shared_ptr<Notifier::INotifier> m_notifier;
            };
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_DATAVALIDATORS_HIERARCHYVALIDATOR_H */