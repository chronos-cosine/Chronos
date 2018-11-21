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
#include "File/Spooler.h"
#include "Sorter/Models/Job.h"

#include <experimental/filesystem>
#include <mutex>
#include <memory>
#include <vector>
#include <thread>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    namespace Services {
    
        class SortingMachine {
        public:
            virtual ~SortingMachine() = default; 
            SortingMachine(const std::vector<fs::path>& paths, 
                           const std::chrono::seconds& sleep_time,
                           const unsigned short& consumer_count);
        public:
            bool start();
            bool stop();
        private:
            void initialise_producers(const std::vector<fs::path>& paths,
                    const std::chrono::seconds& sleep_time);
            void initialise_consumers(const unsigned short& consumer_count);
            void create_producer_threads();
            void create_consumer_threads();
            void stop_producer_threads();
            void stop_consumer_threads();
        private:
            std::shared_ptr<Collections::ICollection<Sorter::Models::Job>> job_collection;
            std::shared_ptr<Collections::ICollection<Sorter::Models::Job>> result_collection;
            std::vector<std::shared_ptr<Processors::IProcessor>> producers;
            std::vector<std::shared_ptr<Processors::IProcessor>> consumers;
            std::vector<std::thread> producer_threads;
            std::vector<std::thread> consumer_threads;
            std::mutex __mutex;
            bool __is_running;
            bool __is_stopping;

        }; /* class SortingMachine */ 
    
    } /* namespace Services */
} /* namespace Sorter */

#endif /* SORTER_SORTINGMACHINE_H */

