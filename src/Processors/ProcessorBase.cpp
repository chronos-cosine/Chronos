/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Processors/IProcessor.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 09 October 2018, 10:52 PM
 */

#include "Processors/ProcessorBase.h" // <-- Header -->
#include "Processors/IProcessor.h"
 
#include <memory>
#include <thread>
#include <chrono>

namespace Processors {

    ProcessorBase::ProcessorBase()
            : __sleep_time(std::chrono::seconds(30)),
              __is_running(false),
              __is_executing(false) {
    }
        
    ProcessorBase::ProcessorBase(const std::chrono::seconds& sleep_time)
            : __sleep_time(sleep_time),
              __is_running(false),
              __is_executing(false) {
    }
    
    bool 
    ProcessorBase::get_is_running() const {
        return __is_running;
    } 
    
    bool 
    ProcessorBase::set_is_running(const bool& value) {
        std::lock_guard<std::mutex> lock (__mutex);
        if (__is_running != value) {
            __is_running = value;
            return true;
        }
        
        return false;
    }
    
    bool 
    ProcessorBase::get_is_executing() const {
        return __is_running;
    } 
        
    void 
    ProcessorBase::stop() {
        set_is_running(false);
    }
    
    void
    ProcessorBase::start() {
        if (!set_is_running(true)) {
            return;
        }
        
        while (__is_running) {
            __is_executing = true;
            
            if (__is_running && !process()) {
                __is_executing = false;
                std::this_thread::sleep_for(__sleep_time);
            }
        }
    } 

} /* namespace Processors */