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
#include "Notifier/Notifiable.h"
#include "Processors/ProcessorBase.h"
#include "Apps/Sorter/Models/Job.h"
#include "Apps/Sorter/Models/Result.h"
#include "Apps/Sorter/Services/IDataProvider.h"
#include "Apps/Sorter/Services/IDataValidator.h"

#include <memory>
#include <string>

namespace Sorter {
    namespace Services {
        
        class SortingProcess : public Processors::ProcessorBase,
                               public Notifier::Notifiable {
        public:
            virtual ~SortingProcess() = default;
            SortingProcess(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& t_jobs,
                           const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& t_results,
                           const std::shared_ptr<Sorter::Data::DataContext>& t_data_context);
            SortingProcess(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& t_jobs,
                           const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& t_results,
                           const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                           const std::shared_ptr<Notifier::INotifier>& t_notifier);
        protected:
            virtual bool process();
        private:
            void init(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context);
            void populate(const std::shared_ptr<Sorter::Models::Job>& t_job);
            void validate(const std::shared_ptr<Sorter::Models::Job>& t_job);
            void remove_invalid(const std::shared_ptr<Sorter::Models::Job>& t_job);
            void save(const std::shared_ptr<Sorter::Models::Job>& t_job);
        private:
            std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>> m_jobs;
            std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>> m_results;
            std::vector<std::shared_ptr<IDataProvider>> m_data_providers;
            std::vector<std::shared_ptr<IDataValidator>> m_data_validators;
            
        }; /* class SortingProcess */

    } /* namespace Services */
} /* namespace Sorter */


#endif /* SORTER_SERVICES_SORTINGPROCESS_H */

