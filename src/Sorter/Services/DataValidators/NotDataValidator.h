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

#include "Sorter/Services/IDataValidator.h"

namespace Sorter {
    namespace Services {
    
        class NotDataValidator : public IDataValidator {
        public:
            virtual ~NotDataValidator() = default;
            NotDataValidator() = default; 
            
            virtual bool process(const std::shared_ptr<Sorter::Models::Job>& job);

        };
    
    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_NOTDATAVALIDATOR_H */

