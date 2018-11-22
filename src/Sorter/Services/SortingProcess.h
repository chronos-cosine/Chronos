/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingProcess.h
 * Author: user
 *
 * Created on 22 November 2018, 9:29 AM
 */

#ifndef SORTER_SERVICES_SORTINGPROCESS_H
#define SORTER_SERVICES_SORTINGPROCESS_H

#include "Collections/ICollection.h"
#include "Processors/ProcessorBase.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Models/Result.h"
#include "IDataProvider.h"
#include "IDataValidator.h"

#include <memory>

namespace Sorter {
    namespace Services {
        
        class SortingProcess : public Processors::ProcessorBase {
        public:
            virtual ~SortingProcess() = default;
            SortingProcess(const std::shared_ptr<Collections::ICollection<Sorter::Models::Job>>& j,
                           const std::shared_ptr<Collections::ICollection<Sorter::Models::Job>>& r);
        protected:
            virtual bool process();
        private:
            std::shared_ptr<Collections::ICollection<Sorter::Models::Job>> jobs;
            std::shared_ptr<Collections::ICollection<Sorter::Models::Job>> results;
            std::vector<std::shared_ptr<IDataProvider>> data_providers;
            std::vector<std::shared_ptr<IDataValidator>> data_validators;
            
        }; /* class SortingProcess */

    } /* namespace Services */
} /* namespace Sorter */


#endif /* SORTER_SERVICES_SORTINGPROCESS_H */

