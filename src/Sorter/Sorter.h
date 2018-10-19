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
 
#include "Collections/ConcurrentQueue.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Processors/IProcessor.h"
#include "Sorter/JobFileReader.h"
#include "Sorter/Pattern.h"
#include "Sorter/ResultFileWriter.h"
#include "Sorter/StartupSettings.h"

#include <boost/filesystem/path.hpp>
#include <memory>
#include <map>
#include <set>

namespace Sorter {
    class Sorter : public Processors::IProcessor {
    private:
        struct completed {
            void operator()(Sorter& sender, 
                            const unsigned long long& total_matches,
                            Job& input) {
                sender.process_job(input);
            }
        };
        struct match_found {
            void operator()(Sorter& sender, 
                            const unsigned long long& position,
                            Job& input,
                            const std::set<std::shared_ptr<Pattern>>& patterns) {
                for (auto& pattern: patterns) {
                    sender.__match_patterns[std::shared_ptr<Job>(&input)][pattern].insert(position);
                    sender.__match_bins[std::shared_ptr<Job>(&input)].insert(pattern->get_bin());
                }
            }
        };
    private:
        unsigned int __sleep_time;
        StartupSettings& __startup_settings;
        Sorter::completed __completed;
        Sorter::match_found __match_found; 
        ResultFileWriter __result_file_writer;
        PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>& __pattern_matching_machine;
        Collections::ConcurrentQueue<boost::filesystem::path>& __concurrent_queue;
        JobFileReader __job_file_reader;
        std::map<std::shared_ptr<Job>, std::map<std::shared_ptr<Pattern>, std::set<unsigned long long>>> __match_patterns;
        std::map<std::shared_ptr<Job>, std::set<std::shared_ptr<Bin>>> __match_bins;
    public:
        Sorter(PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>& pattern_matching_machine,
               Collections::ConcurrentQueue<boost::filesystem::path>& concurrent_queue, 
               const unsigned int& sleep_time,
               StartupSettings& startup_settings);
        virtual ~Sorter();
    protected:
        virtual bool process();
    private:
        void process_job(Job& job);
    public:
        Sorter(Sorter&) = delete;
        Sorter& operator=(Sorter&) = delete;
        Sorter(Sorter&&) = delete;
        Sorter& operator=(Sorter&&) = delete;
    };
    
} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

