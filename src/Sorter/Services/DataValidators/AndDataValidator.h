/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AndDataValidator.h
 * Author: user
 *
 * Created on 22 November 2018, 10:25 AM
 */

#ifndef SORTER_SERVICES_ANDDATAVALIDATOR_H
#define SORTER_SERVICES_ANDDATAVALIDATOR_H

#include "Sorter/Services/IDataValidator.h"

namespace Sorter {
    namespace Services {
    
        class AndDataValidator : public IDataValidator {
        public:
            virtual ~AndDataValidator() = default;
            AndDataValidator() = default;
            
            virtual bool process(const std::shared_ptr<Sorter::Models::Job>& job);
        };
    
    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_ANDDATAVALIDATOR_H */

