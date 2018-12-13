/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OrDataValidator.h
 * Author: user
 *
 * Created on 22 November 2018, 10:25 AM
 */

#ifndef SORTER_SERVICES_DATAVALIDATORS_ORDATAVALIDATOR_H
#define SORTER_SERVICES_DATAVALIDATORS_ORDATAVALIDATOR_H

#include "Notifier/Notifiable.h"
#include "Sorter/Data/DataContext.h"
#include "Sorter/Services/IDataValidator.h"

#include <memory>
#include <string>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
    
            class OrDataValidator : public IDataValidator,
                                    Notifier::Notifiable {
            public:
                virtual ~OrDataValidator() = default;
                OrDataValidator(
                    const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                    const std::shared_ptr<Notifier::INotifier>& t_notifier);
                OrDataValidator(
                    const std::shared_ptr<Sorter::Data::DataContext>& t_data_context);

                virtual void process(const std::shared_ptr<Sorter::Models::Job>& t_job);
            private:
                std::shared_ptr<Sorter::Data::DataContext> m_data_context;
            };
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_DATAVALIDATORS_ORDATAVALIDATOR_H */

