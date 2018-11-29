/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IDataProvider.h
 * Author: user
 *
 * Created on 21 November 2018, 9:51 AM
 */

#ifndef SORTER_SERVICES_IDATAPROVIDER_H
#define SORTER_SERVICES_IDATAPROVIDER_H

#include "Sorter/Models/Job.h"

namespace Sorter {
    namespace Services {
    
        class IDataProvider {
        public:
            virtual ~IDataProvider() = default;
            IDataProvider() = default;
            
            virtual void process(const std::shared_ptr<Sorter::Models::Job>& t_job) = 0;
            
        }; /* class IDataProvider */ 
    
    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_IDATAPROVIDER_H */

