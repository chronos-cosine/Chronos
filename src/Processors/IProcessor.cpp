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

#include <thread>
#include <chrono>

namespace Processors {

    IProcessor::IProcessor(const int& sleep_time, 
                           const std::shared_ptr<Notifier::INotifier>& notifier) 
            : __sleep_time(sleep_time), __notifier(notifier), 
              __is_running(false), __is_executing(false) { 
    }

    IProcessor::~IProcessor() { }
      
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
        std::stringstream notification; 
        
        notification << "Starting " << this;
        __notifier->notify(notification);
        
        if (!set_is_running(true)) {
            notification << this << " already running. Exiting..." << this;
            __notifier->notify(notification);
            
            return;
        }
        
        while (__is_running) {
            notification << this << " looping ";
            __notifier->notify(notification);
            __is_executing = true;
            
            if (__is_running && !process()) {
                notification << this << " sleeping for " << __sleep_time;
                __notifier->notify(notification);
                
                std::this_thread::sleep_for(std::chrono::seconds(__sleep_time));
            }
            
            __is_executing = false;
        }
    }

} /* namespace Processors */