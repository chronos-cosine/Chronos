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

#include "Notifier/INotifier.h"
#include "Notifier/Notifiable.h"

#include <mutex>
#include <memory>

namespace Processors {

    class IProcessor : public Notifier::Notifiable {
    private:
        std::mutex __mutex;
        bool __is_running;
        bool __is_executing;
        int __sleep_time;
        std::shared_ptr<Notifier::INotifier> __notifier;
    public:
        IProcessor(const int& sleep_time, 
                   const std::shared_ptr<Notifier::INotifier>& notifier);
        virtual ~IProcessor();
        
        void start();
        void stop();
        
        bool get_is_running() const; 
        bool get_is_executing() const;
    private:
        bool set_is_running(const bool& value);
        bool set_is_executing(const bool& value);
    protected:
        virtual bool process() = 0;
    public:
        IProcessor(const IProcessor&) = delete;
        IProcessor& operator=(const IProcessor&) = delete;
        IProcessor(const IProcessor&&) = delete;
        IProcessor& operator=(const IProcessor&&) = delete;
    };

} /* namespace Processors */

#endif /* CORE_IPROCESSOR_H */

