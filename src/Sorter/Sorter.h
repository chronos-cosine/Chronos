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

#include "Collections/ICollection.h"
#include "Processors/ProcessorBase.h"
#include "Sorter/BooleanOperator.h"
#include "Sorter/Bin.h"
#include "Sorter/Job.h"
#include "Sorter/Pattern.h"

#include <memory>
#include <map>
#include <set>

namespace Sorter {
    
    class Sorter : public Processors::ProcessorBase {
        Sorter(const Sorter&) = delete;
    public:
        virtual ~Sorter() = default;
        Sorter(std::shared_ptr<std::map<unsigned long long, Bin>> bins,
               std::shared_ptr<std::map<unsigned long long, Pattern>> patterns,
               std::shared_ptr<std::map<unsigned long long, std::map<BooleanOperator, 
                        std::set<Pattern>>>> bin_patterns,
               std::shared_ptr<Collections::ICollection<Job>> jobs);
    protected:
        virtual bool process();
    private:
        std::shared_ptr<std::map<unsigned long long, Bin>> __bins;
        std::shared_ptr<std::map<unsigned long long, Pattern>> __patterns;
        std::shared_ptr<std::map<unsigned long long, std::map<BooleanOperator, 
                        std::set<Pattern>>>> __bin_patterns;
        std::shared_ptr<Collections::ICollection<Job>> __jobs;

    };
} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

