/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IDataValidator.h
 * Author: user
 *
 * Created on 22 November 2018, 9:48 AM
 */

#ifndef SORTER_SERVICES_IDATAVALIDATOR_H
#define SORTER_SERVICES_IDATAVALIDATOR_H

#include "Apps/Sorter/Models/Job.h"

#include <memory>

namespace Sorter {
    namespace Services {
    
        class IDataValidator {
        public:
            virtual ~IDataValidator() = default;
            IDataValidator() = default;
            
            virtual void process(const std::shared_ptr<Sorter::Models::Job>& t_job) = 0;
            
            
        }; /* class IDataProvider */ 
    
    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_IDATAVALIDATOR_H */

