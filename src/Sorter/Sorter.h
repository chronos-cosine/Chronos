/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.h
 * Author: user
 *
 * Created on 12 October 2018, 1:50 PM
 */

#ifndef SORTER_SORTER_H
#define SORTER_SORTER_H
 
#include "Core/ConcurrentQueue.h"
#include "Core/IProcessor.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/JobFileReader.h"
#include "Sorter/Pattern.h"

#include <boost/filesystem/path.hpp>

namespace Sorter {
    
    class Sorter : public Core::IProcessor {
    public:
        Sorter(PatternMatcher::PatternMatchingMachine<std::string, Pattern, Sorter>& pattern_matching_machine,
               Core::ConcurrentQueue<boost::filesystem::path>& concurrent_queue);
        virtual ~Sorter();
    protected:
        virtual bool process();
    private:
        PatternMatcher::PatternMatchingMachine<std::string, Pattern, Sorter>& __pattern_matching_machine;
        Core::ConcurrentQueue<boost::filesystem::path>& __concurrent_queue;
        JobFileReader __job_file_reader;
    };
    
} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

