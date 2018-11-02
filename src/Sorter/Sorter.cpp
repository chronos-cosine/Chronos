/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter/Sorter.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 31 October 2018, 10:52 PM
 */

#include "Sorter.h"
#include "File/JsonDataReader.h"
#include "Processors/IProcessor.h"

#include <memory>

namespace Sorter {
    
    Sorter::~Sorter() {
    }
    
    Sorter::Sorter(const std::shared_ptr<PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>>& matcher,
                   const std::shared_ptr<Collections::ICollection<std::string>>& jobs,
                   const std::shared_ptr<Notifier::INotifier>& notifier)
            : Processors::IProcessor(5, notifier), __matcher(matcher), 
              __jobs(jobs) {
    }
    
    bool 
    Sorter::process() {
        std::string filename = std::move(__jobs->pop());
        std::string message = "Sorter::process() job.id " + filename; 
        notify(message);
        
        std::shared_ptr<Job> job = File::JsonDataReader<Job>::read(filename);
        job->filename = filename;
        __matcher->match(*job, this);
        
        return !__jobs->empty();
    }
      
} /* namespace Sorter */