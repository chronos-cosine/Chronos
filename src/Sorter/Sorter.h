/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 05 November 2018, 7:52 PM
 */

#ifndef SORTER_SORTER_H
#define SORTER_SORTER_H

#include "Processors/ProcessorBase.h"

namespace Sorter {
    
    class Sorter : public Processors::ProcessorBase {
        Sorter(const Sorter&) = delete;
    public:
        virtual ~Sorter() = default;
        Sorter();
    protected:
        virtual bool process();
    private:

    };
} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

