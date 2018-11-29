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
#include "Sorter/Data/DataContext.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Models/Result.h"

#include <experimental/filesystem>
#include <mutex>
#include <memory>
#include <string>
#include <vector>
#include <thread>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    namespace Services {

        class SortingMachine {
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
        public:
            bool start();
            bool stop();
            bool get_is_running() const noexcept;
        private:
            void init(const std::vector<fs::path>& t_paths,
                    const std::chrono::seconds& t_sleep_time,
                    const unsigned short& t_consumer_count);
            void initialise_producers(const std::vector<fs::path>& t_paths,
                    const std::chrono::seconds& t_sleep_time);
            void initialise_consumers(const unsigned short& t_consumer_count);
            void create_producer_threads();
            void create_consumer_threads();
            void stop_producer_threads();
            void stop_consumer_threads();
            void notify(const std::string& t_message);
        private:
            std::shared_ptr<Notifier::INotifier> m_notifier;
            std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>> m_jobs;
            std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>> m_results;
            std::vector<std::shared_ptr<Processors::IProcessor>> m_job_producers;
            std::vector<std::shared_ptr<Processors::IProcessor>> m_job_consumers;
            std::vector<std::thread> m_job_producer_threads;
            std::vector<std::thread> m_job_consumer_threads;
            std::shared_ptr<Sorter::Data::DataContext> m_data_context;
            std::mutex m_mutex;
            bool m_is_running;
            bool m_is_stopping;

        }; /* class SortingMachine */

    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SORTINGMACHINE_H */

