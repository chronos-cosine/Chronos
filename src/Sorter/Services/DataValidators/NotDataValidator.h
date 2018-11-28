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

#ifndef SORTER_SERVICES_NOTDATAVALIDATOR_H
#define SORTER_SERVICES_NOTDATAVALIDATOR_H

#include "Notifier/INotifier.h"
#include "Sorter/Data/DataContext.h"
#include "Sorter/Services/IDataValidator.h"

#include <memory>
#include <string>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
    
            class NotDataValidator : public IDataValidator {
            public:
                virtual ~NotDataValidator() = default;
                NotDataValidator(const std::shared_ptr<Sorter::Data::DataContext>& data_context,
                           const std::shared_ptr<Notifier::INotifier>& notifier);
                NotDataValidator(const std::shared_ptr<Sorter::Data::DataContext>& data_context);

                virtual void process(const std::shared_ptr<Sorter::Models::Job>& job);
            private:
                void notify(const std::string& message) const;
            private:
                std::shared_ptr<Sorter::Data::DataContext> __data_context;
                std::shared_ptr<Notifier::INotifier> __notifier;

            };
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_NOTDATAVALIDATOR_H */

