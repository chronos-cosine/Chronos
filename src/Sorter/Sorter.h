/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter/Sorter.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 31 October 2018, 10:52 PM
 */

#ifndef SORTER_SORTER_H
#define SORTER_SORTER_H

#include "Collections/ICollection.h"
#include "Notifier/NotifierBase.h"
#include "Notifier/Notifiable.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Processors/ProcessorBase.h"
#include "Sorter/Pattern.h"
#include "Sorter/Job.h"

#include <map>
#include <memory>
#include <mutex>
#include <set>

namespace Sorter {
    
    class Sorter : public Processors::ProcessorBase, 
                   public Notifier::Notifiable {
        Sorter() = delete;
        Sorter(const Sorter&) = delete;
        Sorter& operator=(const Sorter&) = delete;
    public:
        virtual ~Sorter() = default;
        Sorter(const std::shared_ptr<PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>>& matcher,
               const std::shared_ptr<Collections::ICollection<std::string>>& jobs,
               const std::shared_ptr<Notifier::INotifier>& notifier);
    protected:
        virtual bool process();
    private:
        std::mutex __mutex;
        std::shared_ptr<Collections::ICollection<std::string>> __jobs;
        std::shared_ptr<PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>> __matcher;
        
    }; /* class Sorter */
    
} /* namespace Sorter */


#endif /* SORTER_SORTER_H */

