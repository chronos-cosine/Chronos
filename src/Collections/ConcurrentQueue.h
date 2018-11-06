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

#ifndef COLLECTIONS_CONCURRENTQUEUE_H
#define COLLECTIONS_CONCURRENTQUEUE_H

#include "Collections/IConcurrentCollection.h"
#include "Collections/CollectionType.h"
#include <condition_variable>
#include <mutex>
#include <queue>

namespace Collections {

    template <typename T>
    class ConcurrentQueue : public IConcurrentCollection<T> {
        ConcurrentQueue(const ConcurrentQueue&) = delete;
    private:
        std::queue<T> queue;
        std::mutex mutex;
        std::condition_variable condition_variable;
    public:
        virtual ~ConcurrentQueue() = default;
        ConcurrentQueue() = default;
        
        virtual void push(T item);
        virtual T pop();
        virtual bool empty() const;
        virtual CollectionType get_collection_type() const;
        typename std::queue<T>::size_type size() const;
        
    }; /* class ConcurrentBag */
    
    template <typename T>
    void 
    ConcurrentQueue<T>::push(T item) {
        std::lock_guard<std::mutex> lock(mutex);
        
        queue.push(std::move(item));
        condition_variable.notify_one();
    } 
    
    template <typename T>
    T 
    ConcurrentQueue<T>::pop() {
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
    ConcurrentQueue<T>::empty() const {
        return queue.empty();
    }
    
    template <typename T>
    CollectionType 
    ConcurrentQueue<T>::get_collection_type() const {
        return Collections::CollectionType::FIFO;
    }
        
    template <typename T>
    typename std::queue<T>::size_type 
    ConcurrentQueue<T>::size() const {
        return queue.size();
    } 
    
} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENTQUEUE_H */

