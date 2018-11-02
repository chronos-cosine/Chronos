/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Collections/ICollection.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 31 October 2018, 10:52 PM
 */

#ifndef COLLECTIONS_ICOLLECTION_H
#define COLLECTIONS_ICOLLECTION_H

#include <condition_variable>
#include <memory>
#include <mutex>

namespace Collections {
    
    template <typename T>
    class ICollection {
        ICollection(const ICollection&) = delete;
        ICollection& operator=(const ICollection&) = delete;
    public:
        virtual ~ICollection() { }
        ICollection() { }
        
        virtual void push(T item) = 0;
        virtual T pop() = 0;
        virtual bool empty() = 0;
    protected:
        std::mutex __mutex;
        std::condition_variable __condition_variable;
        
    }; /* class ICollection */
    
} /* namespace Collections */

#endif /* COLLECTIONS_ICOLLECTION_H */

