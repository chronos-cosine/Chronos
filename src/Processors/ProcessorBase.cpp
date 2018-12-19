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

#include "Processors/ProcessorBase.h"
#include "Processors/IProcessor.h"
 
#include <memory>
#include <thread>
#include <chrono>

namespace Processors {

    ProcessorBase::ProcessorBase()
      : m_sleep_time(std::chrono::seconds(30)),
        m_is_running(false),
        m_is_executing(false),
        m_is_stopping(false) {
    }
        
    ProcessorBase::ProcessorBase(const std::chrono::seconds& sleep_time)
      : m_sleep_time(sleep_time),
        m_is_running(false),
        m_is_executing(false),
        m_is_stopping(false) {
    }
    
    bool 
    ProcessorBase::set_is_running(const bool& t_value) noexcept {
        std::lock_guard<std::mutex> lock(m_mutex);
        
        if (m_is_running != t_value && !m_is_stopping) { 
            m_is_running = t_value;
            m_is_stopping = !m_is_running;
            return true; 
        }
        
        return false;
    }
    
    bool 
    ProcessorBase::set_is_stopping(const bool& t_value) noexcept {
        std::lock_guard<std::mutex> lock (m_mutex);
        
        if (m_is_stopping != t_value) {
            m_is_stopping = t_value;
            return true;
        }
        
        return false;
    }
    
    bool 
    ProcessorBase::get_is_running() const noexcept {
        return m_is_running;
    } 
    
    bool 
    ProcessorBase::get_is_executing() const noexcept {
        return m_is_running;
    } 
        
    bool 
    ProcessorBase::get_is_stopping() const noexcept {
        return m_is_stopping;
    }
    
    bool
    ProcessorBase::start() {
        if (!set_is_running(true)) {
            return false;
        }
        
        while (m_is_running) {
            m_is_executing = true;
            
            if (m_is_running && !process()) {
                m_is_executing = false;
                std::this_thread::sleep_for(m_sleep_time);
            }
        }
        
        m_is_stopping = false;
        return true;
    } 
    
    bool 
    ProcessorBase::stop() {
        return set_is_running(false);
    }

} /* namespace Processors */