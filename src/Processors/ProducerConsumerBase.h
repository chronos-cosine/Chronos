/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProducerConsumerBase.h
 * Author: user
 *
 * Created on 13 December 2018, 8:33 AM
 */

#ifndef PROCESSORS_PRODUCERCONSUMERBASE_H
#define PROCESSORS_PRODUCERCONSUMERBASE_H

#include "Notifier/INotifier.h"
#include "Notifier/Notifiable.h"
#include "Processors/IProcessor.h"
#include "Processors/IRunnable.h"

#include <chrono>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace Processors {
 
    class ProducerConsumerBase : public Notifier::Notifiable,
                                 public IRunnable {
    public:
        virtual ~ProducerConsumerBase() = default;
        ProducerConsumerBase();
        ProducerConsumerBase(const std::shared_ptr<Notifier::INotifier>& t_notifier);
    public:
        virtual bool start();
        virtual bool stop();
        virtual bool get_is_running() const noexcept;
        virtual bool get_is_stopping() const noexcept;
    protected: 
        virtual void create_producer_threads();
        virtual void create_consumer_threads();
        virtual void stop_producer_threads();
        virtual void stop_consumer_threads();
    private:
        std::mutex m_mutex;
        bool m_is_running;
        bool m_is_stopping;
    protected:
        std::vector<std::shared_ptr<Processors::IProcessor>> m_job_producers;
        std::vector<std::shared_ptr<Processors::IProcessor>> m_job_consumers;
        std::vector<std::thread> m_job_producer_threads;
        std::vector<std::thread> m_job_consumer_threads;
    };
    
} /* namespace Processors */

#endif /* PROCESSORS_PRODUCERCONSUMERBASE_H */

