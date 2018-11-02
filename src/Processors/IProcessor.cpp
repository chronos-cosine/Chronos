/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Processors/IProcessor.h"

/* 
 * File:   IProcessor.cpp
 * Author: user
 * 
 * Created on 09 October 2018, 10:54 AM
 */

#include "Notifier/INotifier.h"
 
#include <memory>
#include <thread>
#include <chrono>

namespace Processors {

    IProcessor::~IProcessor() { }
    
    IProcessor::IProcessor()
            : Notifier::Notifiable(std::shared_ptr<Notifier::INotifier>(nullptr)),
              __sleep_time_seconds(30),
              __is_running(false),
              __is_executing(false) {
    } 
    
    IProcessor::IProcessor(const unsigned int& sleep_time_seconds)
            : Notifier::Notifiable(std::shared_ptr<Notifier::INotifier>(nullptr)),
              __sleep_time_seconds(sleep_time_seconds),
              __is_running(false),
              __is_executing(false) {
    }
    
    IProcessor::IProcessor(const unsigned int& sleep_time_seconds,
                           const std::shared_ptr<Notifier::INotifier>& notifier)
            : Notifier::Notifiable(notifier),
              __sleep_time_seconds(sleep_time_seconds),
              __is_running(false),
              __is_executing(false) {
    } 

    bool 
    IProcessor::get_is_running() const {
        return __is_running;
    } 
    
    bool 
    IProcessor::set_is_running(const bool& value) {
        std::lock_guard<std::mutex> lock (__mutex);
        if (__is_running != value) {
            __is_running = value;
            return true;
        }
        
        return false;
    }
    
    bool 
    IProcessor::get_is_executing() const {
        return __is_running;
    } 
        
    void 
    IProcessor::stop() {
        set_is_running(false);
    }
    
    void
    IProcessor::start() {
        if (!set_is_running(true)) {
            notify("Already running. Exiting...");
            return;
        }
        
        while (__is_running) {
            __is_executing = true;
            
            if (__is_running && !process()) {
                __is_executing = false;
                std::this_thread::sleep_for(std::chrono::seconds(__sleep_time_seconds));
            }
        }
    } 

} /* namespace Processors */