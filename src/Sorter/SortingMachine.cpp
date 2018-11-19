/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.cpp
 * Author: user
 * 
 * Created on 19 November 2018, 11:14 AM
 */

#include "Collections/Concurrent/Queue.h"
#include "SortingMachine.h"
#include "Sorter/Models/Job.h"

#include <chrono>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    
    SortingMachine::SortingMachine(const std::vector<fs::path>& paths, 
                       const std::chrono::seconds& sleep_time) 
      : collection(std::make_shared<
            Collections::Concurrent::Queue<Sorter::Models::Job>>()),
        __is_running(false),
        __is_stopping(false) {
        initialise_producers(paths, sleep_time);
        initialise_consumers();
    }
    
    void 
    SortingMachine::initialise_producers(const std::vector<fs::path>& paths, 
            const std::chrono::seconds& sleep_time) {
        for (auto& path: paths) {
            auto producer = std::make_shared<File::Spooler<Sorter::Models::Job>>(path, 
                    ".sjob", ".sdone", sleep_time, collection);
            producers.push_back(std::move(producer));
        }
    }
    
    void 
    SortingMachine::initialise_consumers() {
        
    }
        
    void 
    SortingMachine::create_producer_threads() {
        for (auto& producer: producers) {
            std::thread thread(&Processors::IProcessor::start, producer);
            thread.detach();
            producer_threads.push_back(std::move(thread));
        }
    }
    
    void 
    SortingMachine::create_consumer_threads() {
        for (auto& consumer: consumers) {
            std::thread thread(&Processors::IProcessor::start, consumer);
            thread.detach();
            consumer_threads.push_back(std::move(thread));
        }
    }
    
    void 
    SortingMachine::stop_producer_threads() {
        for (auto& producer: producers) {
            producer->stop();
        }
    }
    
    void 
    SortingMachine::stop_consumer_threads() {
        for (auto& consumer: consumers) {
            consumer->stop();
        }
    }

    bool 
    SortingMachine::start() {
        std::lock_guard<std::mutex> lock(__mutex);
        
        if (__is_running || __is_stopping) { 
            return false;
        }
        
        __is_running = true;
        create_producer_threads();
        create_consumer_threads();
        
        return true;
    }
    
    bool 
    SortingMachine::stop() {
        std::lock_guard<std::mutex> lock(__mutex);
        
        if (!__is_running || __is_stopping) {
            return false;
        }
         
        __is_stopping = true;
        stop_producer_threads();
        stop_consumer_threads();

        producer_threads.clear();
        consumer_threads.clear();

        __is_stopping = false;
        return true;
    }
    
} /* namespace Sorter */
