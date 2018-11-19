/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IDataRepository.h
 * Author: user
 *
 * Created on 19 November 2018, 9:08 AM
 */

#ifndef SORTER_SERVICES_IDATAREPOSITORY_H
#define SORTER_SERVICES_IDATAREPOSITORY_H

#include "Sorter/Data/DataContext.h"

#include <memory>

namespace Sorter {
    namespace Repositories {
        
        class IDataRepository {
            IDataRepository(const IDataRepository&) = delete;
            IDataRepository& operator=(const IDataRepository&) = delete;
        public:
            virtual ~IDataRepository() = default;
            IDataRepository() = default;
            
            virtual std::shared_ptr<Sorter::Data::DataContext> create_data_context() = 0;
        }; /* class IDataRepository */
                
    } /* namespace Repositories */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_IDATAREPOSITORY_H */

