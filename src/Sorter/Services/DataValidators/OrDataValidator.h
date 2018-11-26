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

#ifndef SORTER_SERVICES_ORDATAVALIDATOR_H
#define SORTER_SERVICES_ORDATAVALIDATOR_H

#include "Sorter/Data/DataContext.h"
#include "Sorter/Services/IDataValidator.h"

#include <memory>

namespace Sorter {
    namespace Services {
        namespace DataValidators {
    
            class OrDataValidator : public IDataValidator {
            public:
                virtual ~OrDataValidator() = default;
                OrDataValidator(const std::shared_ptr<Sorter::Data::DataContext>& data_context);

                virtual void process(const std::shared_ptr<Sorter::Models::Job>& job);
            private:
                std::shared_ptr<Sorter::Data::DataContext> __data_context;

            };
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_ORDATAVALIDATOR_H */

