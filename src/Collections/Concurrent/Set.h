/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConcurrentBag.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 6:19 PM
 */

#ifndef COLLECTIONS_CONCURRENTBAG_H
#define COLLECTIONS_CONCURRENTBAG_H

#include "Collections/ICollection.h"
#include <condition_variable>
#include <mutex>
#include <set>

namespace Collections {
    namespace Concurrent {
        
        template <typename T>
        class Set : public ICollection<T> {
            Set(const Set&) = delete; 
            Set& operator=(const Set&) = delete;
            Set(const Set&&) = delete; 
            Set& operator=(const Set&&) = delete;
        private:
            std::set<T> set;
            std::mutex mutex;
            std::condition_variable condition_variable;
        public:
            virtual ~Set() = default;
            Set() = default;

            virtual void push(T item) noexcept;
            virtual T pop() noexcept;
            virtual bool empty() const noexcept;
            typename std::set<T>::size_type size() const noexcept;

        }; /* class Bag */

        template <typename T>
        void 
        Set<T>::push(T item) noexcept {
            std::lock_guard<std::mutex> lock(mutex);

            set.insert(std::move(item));
            condition_variable.notify_one();
        } 

        template <typename T>
        T 
        Set<T>::pop() noexcept {
            std::unique_lock<std::mutex> lock(mutex);

            condition_variable.wait(lock, [this] { 
                return !set.empty(); 
            });
            T item = std::move(*set.begin());
            set.erase(set.begin());

            return item;
        } 

        template <typename T>
        bool 
        Set<T>::empty() const noexcept {
            return set.empty();
        } 

        template <typename T>
        typename std::stack<T>::size_type 
        Set<T>::size() const noexcept {
            return set.size();
        }

    } /* namespace Concurrent */

} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENTBAG_H */

