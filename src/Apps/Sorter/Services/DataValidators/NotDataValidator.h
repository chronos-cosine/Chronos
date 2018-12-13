/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NotDataValidator.h
 * Author: user
 *
 * Created on 22 November 2018, 10:24 AM
 */

#ifndef SORTER_SERVICES_DATAVALIDATORS_NOTDATAVALIDATOR_H
#define SORTER_SERVICES_DATAVALIDATORS_NOTDATAVALIDATOR_H

#include "Notifier/Notifiable.h"
#include "Apps/Sorter/Data/DataContext.h"
#include "Apps/Sorter/Services/IDataValidator.h"

#include <memory>
#include <string>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
    
            class NotDataValidator : public IDataValidator,
                                     Notifier::Notifiable {
            public:
                virtual ~NotDataValidator() = default;
                NotDataValidator(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                           const std::shared_ptr<Notifier::INotifier>& t_notifier);
                NotDataValidator(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context);

                virtual void process(const std::shared_ptr<Sorter::Models::Job>& t_job);
            private:
                std::shared_ptr<Sorter::Data::DataContext> m_data_context;
            }; /* class NotDataValidator */
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_DATAVALIDATORS_NOTDATAVALIDATOR_H */

