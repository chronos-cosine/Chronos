/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IMap.h
 * Author: user
 *
 * Created on 21 November 2018, 10:39 AM
 */

#ifndef COLLECTIONS_IMAP_H
#define COLLECTIONS_IMAP_H

namespace Collections {
    
    template <typename KEY, typename VALUE>
    class IMap {
        IMap(const IMap&) = delete;
        IMap& operator=(const IMap&) = delete;
        IMap(const IMap&&) = delete;
        IMap& operator=(const IMap&&) = delete;
    public:
        virtual ~IMap() = default;
        IMap() = default;
        
        virtual bool exist(const KEY& key) = 0;
        virtual void insert(const KEY& key, const VALUE& value) = 0;
        virtual void erase(const KEY& key) = 0;
        virtual VALUE& at(const KEY& key) = 0;
        virtual VALUE& operator[](const KEY& key) = 0;
        
    }; /* class IMap */
    
    
    
} /* namespace Collections */

#endif /* COLLECTIONS_IMAP_H */

