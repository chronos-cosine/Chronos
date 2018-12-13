/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.h
 * Author: user
 *
 * Created on 19 November 2018, 11:14 AM
 */

#ifndef SORTER_SORTINGMACHINE_H
#define SORTER_SORTINGMACHINE_H

#include "Collections/ICollection.h"
#include "Notifier/INotifier.h"
#include "Processors/IProcessor.h"
#include "Processors/ProducerConsumerBase.h"
#include "Apps/Sorter/Data/DataContext.h"
#include "Apps/Sorter/Models/Job.h"
#include "Apps/Sorter/Models/Result.h"

#include <experimental/filesystem>
#include <mutex>
#include <memory>
#include <string>
#include <vector>
#include <thread>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    namespace Services {

        class SortingMachine : public Processors::ProducerConsumerBase {
        public:
            virtual ~SortingMachine() = default;
            SortingMachine(const std::vector<fs::path>& t_paths,
                    const std::chrono::seconds& t_sleep_time,
                    const unsigned short& t_consumer_count,
                    const std::shared_ptr<Sorter::Data::DataContext>& t_data_context);
            SortingMachine(const std::vector<fs::path>& t_paths,
                    const std::chrono::seconds& t_sleep_time,
                    const unsigned short& t_consumer_count,
                    const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                    const std::shared_ptr<Notifier::INotifier>& t_notifier);
        private:
            void init(const std::vector<fs::path>& t_paths,
                    const std::chrono::seconds& t_sleep_time,
                    const unsigned short& t_consumer_count);
            void initialise_producers(const std::vector<fs::path>& t_paths,
                    const std::chrono::seconds& t_sleep_time);
            void initialise_consumers(const unsigned short& t_consumer_count);
        private:
            std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>> m_jobs;
            std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>> m_results;
            std::shared_ptr<Sorter::Data::DataContext> m_data_context;

        }; /* class SortingMachine */

    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SORTINGMACHINE_H */

