/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.cpp
 * Author: user
 * 
 * Created on 31 October 2018, 9:03 AM
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
            : Processors::IProcessor(30, notifier), __matcher(matcher), 
              __jobs(jobs) {
    }
    
    bool 
    Sorter::process() {
        std::string filename = std::move(__jobs->pop());
        Job job = File::JsonDataReader<Job>::read(filename);
        job.filename = filename;
        
        std::string message = "Sorter::process() job.id " + 
                              std::to_string(job.id);
        notify(message);
        
        __matcher->match(job, this);
        
        return !__jobs->empty();
    }
      
} /* namespace Sorter */