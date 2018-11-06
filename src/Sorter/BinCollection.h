/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinCollection.h
 * Author: user
 *
 * Created on 06 November 2018, 2:00 PM
 */

#ifndef SORTER_BINCOLLECTION_H
#define SORTER_BINCOLLECTION_H

#include "Sorter/Bin.h"
#include "Sorter/BooleanOperator.h"
#include "Sorter/Pattern.h"

#include <memory>

namespace Sorter {
    
    template <typename T>
    class BinCollection {
        BinCollection(const BinCollection&) = delete;
    public:
        virtual ~BinCollection() = default;
        BinCollection() = default;
        
        std::shared_ptr<T>& operator[](const unsigned long long& id);
        const std::shared_ptr<T>& operator[](const unsigned long long& id) const;
        
        std::shared_ptr<T>& operator[](const T& item);
        const std::shared_ptr<T>& operator[](const T& item) const;
    private:
        std::map<unsigned long long, std::shared_ptr<Bin>> __bins;
        std::shared_ptr<std::map<unsigned long long, std::map<BooleanOperator,
                            std::set<std::shared_ptr<Pattern>>>>> __bin_patterns;

    }; /* class BinCollection */
    
} /* namespace Sorter */

    

#endif /* SORTER_BINCOLLECTION_H */

