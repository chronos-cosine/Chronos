/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Collections/ConcurrentQueue.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 12 October 2018, 10:52 PM
 */

#ifndef COLLECTIONS_CONCURRENT_QUEUE_H
#define COLLECTIONS_CONCURRENT_QUEUE_H

#include "Collections/ICollection.h"
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

namespace Collections {
    namespace Concurrent {

        template <typename T>
        class Queue : public ICollection<T> {
            Queue(const Queue&) = delete;
            Queue& operator=(const Queue&) = delete;
            Queue(const Queue&&) = delete; 
            Queue& operator=(const Queue&&) = delete;
        private:
            std::queue<T> queue;
            std::mutex mutex;
            std::condition_variable condition_variable;
        public:
            virtual ~Queue() = default;
            Queue() = default;

            virtual void push(T item) noexcept;
            virtual T pop() noexcept;
            virtual bool empty() const noexcept;
            typename std::queue<T>::size_type size() const noexcept;

        }; /* class Queue */

        template <typename T>
        void 
        Queue<T>::push(T item) noexcept {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Queue<T>::push()" 
                      << std::endl;

            queue.push(std::move(item));
            condition_variable.notify_one();
        } 

        template <typename T>
        T 
        Queue<T>::pop() noexcept {
            std::unique_lock<std::mutex> lock(mutex);

            condition_variable.wait(lock, [this] { 
                return !queue.empty(); 
            });

            std::cout << "Queue<T>::pop()" 
                      << std::endl;
            T item = std::move(queue.front());
            queue.pop();

            return item;
        } 

        template <typename T>
        bool 
        Queue<T>::empty() const noexcept {
            return queue.empty();
        }

        template <typename T>
        typename std::queue<T>::size_type 
        Queue<T>::size() const noexcept {
            return queue.size();
        } 
    
    } /* namespace Concurrent */
    
} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENT_QUEUE_H */

