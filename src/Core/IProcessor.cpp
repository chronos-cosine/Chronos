/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IProcessor.cpp
 * Author: user
 * 
 * Created on 09 October 2018, 10:54 AM
 */

#include "Core/IProcessor.h"
#include "Core/INotifier.h"

#include <thread>
#include <chrono>

namespace Core {

    IProcessor::IProcessor(const int& sleep_time) 
        : __notifier(nullptr), __sleep_time(sleep_time) {
    }

    IProcessor::IProcessor(const int& sleep_time, INotifier* notifier) 
        : __notifier(notifier), __sleep_time(sleep_time) {
    }
    
    IProcessor::~IProcessor() { 
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
    
    bool 
    IProcessor::set_is_executing(const bool& value) {
        std::lock_guard<std::mutex> lock (__mutex);
        if (__is_executing != value) {
            __is_executing = value;
            return true;
        }
        
        return false;
    }
    
    void
    IProcessor::notify(const char* message) {
        if (nullptr != __notifier) {
            __notifier->notify(message);
        }
    }
    
    void 
    IProcessor::clear_notifications() {
        if (nullptr != __notifier) {
            __notifier->clear();
        }
    }
    
    void 
    IProcessor::stop() {
        std::lock_guard<std::mutex> lock (__mutex);
        set_is_running(false);
    }
    
    void
    IProcessor::start() {
        if (!set_is_running(true)) {
            return;
        }
        
        while (__is_running) {
            set_is_executing(true);
            ++__cycle;
            clear_notifications();
            notify("cycling...");
            
            if (!process()
                && __is_running) {
                notify("sleeping...");
                std::this_thread::sleep_for(std::chrono::seconds(__sleep_time));
            }
            
            set_is_executing(false);
        }
    }

} /* namespace Core */