/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Processors/ProducerConsumerBase.h"

namespace Processors {
    
    ProducerConsumerBase::ProducerConsumerBase() 
      :  m_is_running(false),
         m_is_stopping(false),
         Notifier::Notifiable::Notifiable() {
    }
    
    ProducerConsumerBase::ProducerConsumerBase(const std::shared_ptr<Notifier::INotifier>& t_notifier) 
      :  m_is_running(false),
         m_is_stopping(false),
         Notifier::Notifiable::Notifiable(t_notifier) {
    }
 
    void 
    ProducerConsumerBase::create_producer_threads() {
        notify("ProducerConsumerBase::create_producer_threads()");

        for (auto& producer: m_job_producers) {
            std::thread thread(&Processors::IProcessor::start, producer);
            thread.detach();
            m_job_producer_threads.push_back(std::move(thread));
        }
    }

    void 
    ProducerConsumerBase::create_consumer_threads() {
        notify("ProducerConsumerBase::create_consumer_threads()");

        for (auto& consumer: m_job_consumers) {
            std::thread thread(&Processors::IProcessor::start, consumer);
            thread.detach();
            m_job_consumer_threads.push_back(std::move(thread));
        }
    }

    void 
    ProducerConsumerBase::stop_producer_threads() {
        notify("ProducerConsumerBase::stop_producer_threads()");

        for (auto& producer: m_job_producers) {
            producer->stop();
        }
    }

    void 
    ProducerConsumerBase::stop_consumer_threads() {
        notify("ProducerConsumerBase::stop_consumer_threads()");

        for (auto& consumer: m_job_consumers) {
            consumer->stop();
        }
    }

    bool 
    ProducerConsumerBase::get_is_running() const noexcept {
        return m_is_running && !m_is_stopping;
    }
    
    bool
    ProducerConsumerBase::get_is_stopping() const noexcept {
        return m_is_stopping;
    }

    bool 
    ProducerConsumerBase::start() {
        notify("ProducerConsumerBase::start()");

        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_is_running || m_is_stopping) { 
            return false;
        }

        m_is_running = true;
        create_producer_threads();
        create_consumer_threads();

        return true;
    }

    bool 
    ProducerConsumerBase::stop() {
        notify("ProducerConsumerBase::stop()");

        std::lock_guard<std::mutex> lock(m_mutex);

        if (!m_is_running || m_is_stopping) {
            return false;
        }

        m_is_stopping = true;
        stop_producer_threads();
        stop_consumer_threads();

        m_job_producer_threads.clear();
        m_job_consumer_threads.clear();

        m_is_stopping = false;
        return true;
    }

} /* namespace Processors */