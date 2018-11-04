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

#ifndef CORE_PROCESSORBASE_H
#define CORE_PROCESSORBASE_H

#include "Processors/IProcessor.h"

#include <chrono>
#include <mutex>
#include <memory>

namespace Processors {

    class ProcessorBase : public IProcessor {
    private:
        std::mutex __mutex;
        bool __is_running;
        bool __is_executing;
        bool __is_stopping;
        std::chrono::seconds __sleep_time;
    public:
        virtual ~ProcessorBase() = default;
        ProcessorBase();
        ProcessorBase(const std::chrono::seconds& sleep_time);
        
        virtual void start();
        virtual void stop();
        
        bool get_is_stopping() const;
        bool get_is_running() const; 
        bool get_is_executing() const;
    protected:
        bool set_is_stopping(const bool& value);
    private:
        bool set_is_running(const bool& value);
        
    }; /* class ProcessorBase */

} /* namespace Processors */

#endif /* CORE_PROCESSORBASE_H */

