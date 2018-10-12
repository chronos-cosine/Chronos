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

#include <thread>
#include <chrono>

namespace Core {

    IProcessor::IProcessor(const int& sleep_time) 
              : __sleep_time(sleep_time) { }

    IProcessor::~IProcessor() { }
    
    IProcessor::IProcessor(const IProcessor&& move)
              : __is_running(std::move(move.__is_running)), __is_executing(std::move(move.__is_executing)),
                __sleep_time(std::move(move.__sleep_time)) { }
            
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
            return;
        }
        
        while (__is_running) {
            __is_executing = true;
            
            if (!process()
                && __is_running) {
                std::this_thread::sleep_for(std::chrono::seconds(__sleep_time));
            }
            
            __is_executing = false;
        }
    }
    
    IProcessor& 
    IProcessor::operator=(const IProcessor&& move) {
        __is_running = std::move(move.__is_running); 
        __is_executing = std::move(move.__is_executing);
        __sleep_time = std::move(move.__sleep_time);
        
        return *this;
    }

} /* namespace Core */