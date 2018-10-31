/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ICollection.h
 * Author: user
 *
 * Created on 31 October 2018, 9:25 AM
 */

#ifndef COLLECTIONS_ICOLLECTION_H
#define COLLECTIONS_ICOLLECTION_H

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
    protected:
        std::condition_variable __condition_variable;
        std::mutex __mutex;
    };
    
} /* namespace Collections */


#endif /* COLLECTIONS_ICOLLECTION_H */

