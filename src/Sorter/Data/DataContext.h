/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataContext.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 16 November 2018, 8:47 PM
 */

#ifndef SORTER_DATA_DATACONTEXT_H
#define SORTER_DATA_DATACONTEXT_H

#include "Sorter/Models/Bin.h"
#include "Sorter/Models/Pattern.h"

#include <map>
#include <memory>
#include <set>

namespace Sorter {
    namespace Data {
        
        class DataContext {
            DataContext(const DataContext&) = delete;
            DataContext& operator=(const DataContext&) = delete;
            DataContext(DataContext&&) = delete;
            DataContext& operator=(DataContext&&) = delete;
        public:
            virtual ~DataContext() = default;
            DataContext() = default;
            
            void link_bin_patterns();
            void clear();
            
            std::map<unsigned long long, std::shared_ptr<Sorter::Models::Bin>> bins;
            std::map<unsigned long long, std::shared_ptr<Sorter::Models::Pattern>> patterns;
            
        }; /* class DataContext */
                
    } /* namespace Data */
} /* namespace Sorter */

#endif /* SORTER_DATA_DATACONTEXT_H */

