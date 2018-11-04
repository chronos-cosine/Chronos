/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 9:09 PM
 */

#ifndef SORTER_SORTER_H
#define SORTER_SORTER_H

#include "Processors/ProcessorBase.h"

#include <vector>

namespace Sorter {
    
    class ISorterDataProvider;
    class ISorterDataValidator;
    
    class Sorter : public Processors::ProcessorBase {
        Sorter(const Sorter&) = delete;
    public:
        virtual ~Sorter() = default;
        Sorter();
        
        virtual void start();
        virtual void stop();
    protected:
        virtual bool process();
    private:
        std::vector<ISorterDataProvider> __data_providers;
        std::vector<std::thread> __spooler_threads;
        std::vector<ISorterDataValidator> __data_validator;
        
    }; /* class Sorter */
    
} /* namespace Sorter */


#endif /* SORTER_SORTER_H */

