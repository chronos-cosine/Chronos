/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.h
 * Author: user
 *
 * Created on 31 October 2018, 9:03 AM
 */

#ifndef SORTER_SORTER_H
#define SORTER_SORTER_H

#include "Collections/ICollection.h"
#include "Notifier/INotifier.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Processors/IProcessor.h"
#include "Sorter/Pattern.h"
#include "Sorter/Job.h"

#include <map>
#include <memory>
#include <set>

namespace Sorter {
    
    class Sorter : public Processors::IProcessor {
        Sorter(const Sorter&) = delete;
        Sorter& operator=(const Sorter&) = delete;
    public:
        virtual ~Sorter();
        Sorter(const std::shared_ptr<PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>>& matcher,
               const std::shared_ptr<Collections::ICollection<std::string>>& jobs,
               const std::shared_ptr<Notifier::INotifier>& notifier);
    public:
    protected:
        virtual bool process(); 
    private:
        std::shared_ptr<Collections::ICollection<std::string>> __jobs;
        std::shared_ptr<PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>> __matcher;
        
    }; /* class Sorter */
    
} /* namespace Sorter */


#endif /* SORTER_SORTER_H */

