/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.h
 * Author: user
 *
 * Created on 21 November 2018, 10:42 AM
 */

#ifndef COLLECTIONS_CONCURRENT_MAP_H
#define COLLECTIONS_CONCURRENT_MAP_H

#include "Collections/IMap.h"

#include <condition_variable>
#include <iostream>
#include <map>
#include <mutex>

namespace Collections {
    namespace Concurrent {
        
        template <typename KEY, typename VALUE>
        class Map : public Collections::IMap<KEY, VALUE> {
        public:
            virtual ~Map() = default;
            Map() = default;
            
            virtual bool exist(const KEY& key);
            virtual void insert(const KEY& key, const VALUE& value);
            virtual void erase(const KEY& key);
            virtual VALUE& at(const KEY& key);
            virtual VALUE& operator[](const KEY& key);
                   
        private:
            std::mutex mutex;
            std::map<KEY, VALUE> map;
        };
                
        template <typename KEY, typename VALUE>
        bool 
        Map<KEY, VALUE>::exist(const KEY& key){
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Map<KEY, VALUE>::exist()" << std::endl;
            
            return map.find(key) != map.end();
        }
            
        template <typename KEY, typename VALUE>
        void  
        Map<KEY, VALUE>::insert(const KEY& key, const VALUE& value) {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Map<KEY, VALUE>::insert()" << std::endl;
            
            map[key] = value;
        }
            
        template <typename KEY, typename VALUE>
        void  
        Map<KEY, VALUE>::erase(const KEY& key) {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Map<KEY, VALUE>::erase()" << std::endl;
            
            map.erase(key);
        }
            
        template <typename KEY, typename VALUE>
        VALUE&  
        Map<KEY, VALUE>::at(const KEY& key) {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Map<KEY, VALUE>::at()" << std::endl;
            
            return map.at(key);
        }
            
        template <typename KEY, typename VALUE>
        VALUE&  
        Map<KEY, VALUE>::operator[](const KEY& key) {
            std::cout << "Map<KEY, VALUE>::operator[]" << std::endl;
            return at(key);
        }

    } /* namespace Concurrent */
} /* namespace Collections */

#endif /* COLLECTIONS_CONCURRENT_MAP_H */

