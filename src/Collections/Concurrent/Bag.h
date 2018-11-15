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
#include "Collections/CollectionType.h"
#include <condition_variable>
#include <mutex>
#include <set>

namespace Collections {
    namespace Concurrent {
        
        template <typename T>
        class Bag : public ICollection<T> {
            Bag(const Bag&) = delete; 
            Bag& operator=(const Bag&) = delete;
            Bag(const Bag&&) = delete; 
            Bag& operator=(const Bag&&) = delete;
        private:
            std::set<T> set;
            std::mutex mutex;
            std::condition_variable condition_variable;
        public:
            virtual ~Bag() = default;
            Bag() = default;

            virtual void push(T item) noexcept;
            virtual T pop() noexcept;
            virtual bool empty() const noexcept;
            virtual CollectionType get_collection_type() const noexcept;
            typename std::set<T>::size_type size() const noexcept;

        }; /* class Bag */

        template <typename T>
        void 
        Bag<T>::push(T item) noexcept {
            std::lock_guard<std::mutex> lock(mutex);

            set.insert(std::move(item));
            condition_variable.notify_one();
        } 

        template <typename T>
        T 
        Bag<T>::pop() noexcept {
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
        Bag<T>::empty() const noexcept {
            return set.empty();
        } 

        template <typename T>
        CollectionType 
        Bag<T>::get_collection_type() const noexcept {
            return Collections::CollectionType::SORTED;
        }

        template <typename T>
        typename std::stack<T>::size_type 
        Bag<T>::size() const noexcept {
            return set.size();
        }

    } /* namespace Concurrent */

} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENTBAG_H */

