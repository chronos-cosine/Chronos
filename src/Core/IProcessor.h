/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IProcessor.h
 * Author: user
 *
 * Created on 09 October 2018, 10:54 AM
 */

#ifndef CORE_IPROCESSOR_H
#define CORE_IPROCESSOR_H

#include <mutex>

namespace Core {

    class IProcessor {
    public:
        IProcessor(const IProcessor&) = delete;
        IProcessor& operator=(const IProcessor&) = delete;
    public:
        IProcessor(const IProcessor&& move);
        IProcessor(const int& sleep_time);
        virtual ~IProcessor();
        
        virtual void start();
        virtual void stop();
        
        virtual bool get_is_running() const; 
        virtual bool get_is_executing() const; 
        
        virtual IProcessor& operator=(const IProcessor&& move);
    private:
        bool set_is_running(const bool& value);
        bool set_is_executing(const bool& value);
    protected:
        virtual bool process() = 0;
    private:
        bool __is_running;
        bool __is_executing;
        std::mutex __mutex;
        int __sleep_time;
    };

} /* namespace Core */

#endif /* CORE_IPROCESSOR_H */

