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

    template <typename T>
    class ConcurrentBag : public ICollection<T> {
        ConcurrentBag(const ConcurrentBag&) = delete;
    private:
        std::set<T> set;
        std::mutex mutex;
        std::condition_variable condition_variable;
    public:
        virtual ~ConcurrentBag() = default;
        ConcurrentBag() = default;
        
        virtual void push(T item);
        virtual T pop();
        virtual bool empty() const;
        virtual CollectionType get_collection_type() const;
        typename std::set<T>::size_type size() const;
        
    }; /* class ConcurrentStack */
        
    template <typename T>
    void 
    ConcurrentBag<T>::push(T item) {
        std::lock_guard<std::mutex> lock(mutex);
        
        set.insert(std::move(item));
        condition_variable.notify_one();
    } 
    
    template <typename T>
    T 
    ConcurrentBag<T>::pop() {
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
    ConcurrentBag<T>::empty() const {
        return set.empty();
    } 
    
    template <typename T>
    CollectionType 
    ConcurrentBag<T>::get_collection_type() const {
        return Collections::CollectionType::SORTED;
    }
    
    template <typename T>
    typename std::stack<T>::size_type 
    ConcurrentBag<T>::size() const {
        return set.size();
    }
    
} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENTBAG_H */

