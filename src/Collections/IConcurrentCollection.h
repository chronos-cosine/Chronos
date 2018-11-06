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

#include "Collections/CollectionType.h"
#include <condition_variable>
#include <memory>
#include <mutex>

namespace Collections {
    
    template <typename T>
    class IConcurrentCollection {
        IConcurrentCollection(const IConcurrentCollection&) = delete;
    public:
        virtual ~IConcurrentCollection() = default;
        IConcurrentCollection() = default;
        
        virtual void push(T item) = 0;
        virtual T pop() = 0;
        virtual bool empty() const = 0;
        virtual CollectionType get_collection_type() const = 0;
        
    }; /* class ICollection */
    
} /* namespace Collections */

#endif /* COLLECTIONS_ICOLLECTION_H */

