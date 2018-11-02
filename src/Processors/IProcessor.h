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

#include "Notifier/Notifiable.h"
#include <mutex>
#include <memory>

namespace Processors {

    class IProcessor : public Notifier::Notifiable {
    private:
        std::mutex __mutex;
        bool __is_running;
        bool __is_executing;
        unsigned int __sleep_time_seconds;
    public:
        virtual ~IProcessor();
        IProcessor();
        IProcessor(const unsigned int& sleep_time_seconds);
        IProcessor(const unsigned int& sleep_time_seconds, 
                   const std::shared_ptr<Notifier::INotifier>& notifier);
        
        virtual void start();
        virtual void stop();
        
        bool get_is_running() const; 
        bool get_is_executing() const;
    private:
        bool set_is_running(const bool& value);
        bool set_is_executing(const bool& value);
    protected:
        virtual bool process() = 0;
    };

} /* namespace Processors */

#endif /* CORE_IPROCESSOR_H */

