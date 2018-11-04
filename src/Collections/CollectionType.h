/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Type.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 6:10 PM
 */

#ifndef COLLECTIONS_TYPE_H
#define COLLECTIONS_TYPE_H

#include <stdexcept>
#include <string>

namespace Collections {
    
    enum CollectionType {
        FIFO = 0,
        LIFO = 1,
        SORTED = 2
    };
    
    static CollectionType to_collection_type(const std::string& value) {
        if ("fifo" == value) {
            return CollectionType::FIFO;
        } else if ("lifo" == value) {
            return CollectionType::LIFO;
        } else if ("sorted" == value) {
            return CollectionType::SORTED;
        } else {
            throw std::runtime_error("Collections::to_collection_type() collection type not yet supported");
        }
    }
    
} /* namespace Collections */

#endif /* COLLECTIONS_TYPE_H */

