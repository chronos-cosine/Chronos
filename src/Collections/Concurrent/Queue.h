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
#include "Collections/CollectionType.h"
#include <condition_variable>
#include <mutex>
#include <queue>

namespace Collections {
    namespace Concurrent {

        template <typename T>
        class Queue : public ICollection<T> {
            Queue(const Queue&) = delete;
        private:
            std::queue<T> queue;
            std::mutex mutex;
            std::condition_variable condition_variable;
        public:
            virtual ~Queue() = default;
            Queue() = default;

            virtual void push(T item);
            virtual T pop();
            virtual bool empty() const;
            virtual CollectionType get_collection_type() const;
            typename std::queue<T>::size_type size() const;

        }; /* class Queue */

        template <typename T>
        void 
        Queue<T>::push(T item) {
            std::lock_guard<std::mutex> lock(mutex);

            queue.push(std::move(item));
            condition_variable.notify_one();
        } 

        template <typename T>
        T 
        Queue<T>::pop() {
            std::unique_lock<std::mutex> lock(mutex);

            condition_variable.wait(lock, [this] { 
                return !queue.empty(); 
            });

            T item = std::move(queue.front());
            queue.pop();

            return item;
        } 

        template <typename T>
        bool 
        Queue<T>::empty() const {
            return queue.empty();
        }

        template <typename T>
        CollectionType 
        Queue<T>::get_collection_type() const {
            return Collections::CollectionType::FIFO;
        }

        template <typename T>
        typename std::queue<T>::size_type 
        Queue<T>::size() const {
            return queue.size();
        } 
    
    } /* namespace Concurrent */
    
} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENT_QUEUE_H */

