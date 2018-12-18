/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Processors/IProcessor.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 09 October 2018, 10:52 PM
 */

#ifndef PROCESSORS_PROCESSORBASE_H
#define PROCESSORS_PROCESSORBASE_H

#include "Processors/IProcessor.h"

#include <chrono>
#include <mutex>
#include <memory>

namespace Processors {

    class ProcessorBase : public IProcessor {
    private:
        std::mutex m_mutex;
        bool m_is_running;
        bool m_is_executing;
        bool m_is_stopping;
        std::chrono::seconds m_sleep_time;
    public:
        virtual ~ProcessorBase() = default;
        ProcessorBase();
        ProcessorBase(const std::chrono::seconds& t_sleep_time);
        
        virtual bool start();
        virtual bool stop();
        
        virtual bool get_is_stopping() const noexcept;
        virtual bool get_is_running() const noexcept; 
        bool get_is_executing() const noexcept;
    protected:
        bool set_is_stopping(const bool& t_value) noexcept;
    private:
        bool set_is_running(const bool& t_value) noexcept;
        
    }; /* class ProcessorBase */

} /* namespace Processors */

#endif /* CORE_PROCESSORBASE_H */

