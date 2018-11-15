/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Collections/ConcurrentStack.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 26 October 2018, 10:52 PM
 */

#ifndef COLLECTIONS_CONCURRENT_STACK_H
#define COLLECTIONS_CONCURRENT_STACK_H

#include "Collections/ICollection.h"
#include "Collections/CollectionType.h"
#include <condition_variable>
#include <mutex>
#include <stack>

namespace Collections {
    namespace Concurrent {

        template <typename T>
        class Stack : public ICollection<T> {
            Stack(const Stack&) = delete;
        private:
            std::stack<T> stack;
            std::mutex mutex;
            std::condition_variable condition_variable;
        public:
            virtual ~Stack() = default;
            Stack() = default;

            virtual void push(T item);
            virtual T pop();
            virtual bool empty() const;
            virtual CollectionType get_collection_type() const;
            typename std::stack<T>::size_type size() const;

        }; /* class Stack */

        template <typename T>
        void 
        Stack<T>::push(T item) {
            std::lock_guard<std::mutex> lock(mutex);

            stack.push(std::move(item));
            condition_variable.notify_one();
        } 

        template <typename T>
        T 
        Stack<T>::pop() {
            std::unique_lock<std::mutex> lock(mutex);

            condition_variable.wait(lock, [this] { 
                return !__stack.empty(); 
            });
            T item = std::move(stack.top());
            stack.pop();

            return item;
        } 

        template <typename T>
        bool 
        Stack<T>::empty() const {
            return stack.empty();
        } 

        template <typename T>
        CollectionType 
        Stack<T>::get_collection_type() const {
            return Collections::CollectionType::LIFO;
        }

        template <typename T>
        typename std::stack<T>::size_type 
        Stack<T>::size() const {
            return stack.size();
        }
    
    } /* namespace Concurrent */
    
} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENT_STACK_H */

