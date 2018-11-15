/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tree.h
 * Author: user
 *
 * Created on 15 November 2018, 2:01 PM
 */

#ifndef SORTER_MODELS_TREE_H
#define SORTER_MODELS_TREE_H

#include "Bin.h"

#include <map>
#include <set>

namespace Sorter {
    namespace Models {
        
        class Bins {
            Bins(const Bins&) = delete;
            Bins& operator=(const Bins&) = delete;
            Bins(const Bins&&) = delete;
            Bins& operator=(const Bins&&) = delete;
            
        public:
            virtual ~Bins() = default;
            Bins() = default;
        public:
            Bin& get(unsigned long long id); 
            void init_children();
            Bin& operator[](unsigned long long id);
        private:
            std::map<unsigned long long, Bin> __bins;
            std::map<unsigned long long, std::set<unsigned long long>> __children;
        };
        
    } /* namespace Models */
} /* namespace Sorter */


#endif /* SORTER_MODELS_TREE_H */

