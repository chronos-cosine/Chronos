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
#include "Notifier/INotifier.h"
#include "Processors/ProcessorBase.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Models/Result.h"
#include "Sorter/Services/IDataProvider.h"
#include "Sorter/Services/IDataValidator.h"

#include <memory>
#include <string>

namespace Sorter {
    namespace Services {
        
        class SortingProcess : public Processors::ProcessorBase {
        public:
            virtual ~SortingProcess() = default;
            SortingProcess(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& jobs,
                           const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& results,
                           const std::shared_ptr<Sorter::Data::DataContext>& dc);
            SortingProcess(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& jobs,
                           const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& results,
                           const std::shared_ptr<Sorter::Data::DataContext>& dc,
                           const std::shared_ptr<Notifier::INotifier> notifier);
        protected:
            virtual bool process();
        private:
            void init(const std::shared_ptr<Sorter::Data::DataContext>& dc);
            void populate(const std::shared_ptr<Sorter::Models::Job>& job);
            void validate(const std::shared_ptr<Sorter::Models::Job>& job);
            void remove_invalid(const std::shared_ptr<Sorter::Models::Job>& job);
            void save(const std::shared_ptr<Sorter::Models::Job>& job);
            void notify(const std::string& message);
        private:
            std::shared_ptr<Notifier::INotifier> __notifier;
            std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>> __jobs;
            std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>> __results;
            std::vector<std::shared_ptr<IDataProvider>> __data_providers;
            std::vector<std::shared_ptr<IDataValidator>> __data_validators;
            
        }; /* class SortingProcess */

    } /* namespace Services */
} /* namespace Sorter */


#endif /* SORTER_SERVICES_SORTINGPROCESS_H */

