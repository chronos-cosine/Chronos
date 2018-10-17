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
#include "Sorter/ResultFileWriter.h"

#include <boost/filesystem/path.hpp>
#include <memory>
#include <map>
#include <set>

namespace Sorter {
    class Sorter : public Core::IProcessor {
    private:
        struct completed {
            void operator()(Sorter& sender, 
                            const unsigned long long& total_matches,
                            const Job& input) {
                sender.process_job(input);
            }
        };
        struct match_found {
            void operator()(Sorter& sender, 
                            const unsigned long long& position,
                            const Job& input,
                            const std::set<std::shared_ptr<Pattern>>& patterns) {
                for (auto& pattern: patterns) {
                    sender.__match_patterns[input][pattern].insert(position);
                    sender.__match_bins[input].insert(pattern->get_bin());
                }
            }
        };
    private:
        Sorter::completed __completed;
        Sorter::match_found __match_found;
        std::string __output_directory;
        ResultFileWriter __result_file_writer;
        PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>& __pattern_matching_machine;
        Core::ConcurrentQueue<boost::filesystem::path>& __concurrent_queue;
        JobFileReader __job_file_reader;
        std::map<Job, std::map<std::shared_ptr<Pattern>, std::set<unsigned long long>>> __match_patterns;
        std::map<Job, std::set<std::shared_ptr<Bin>>> __match_bins;
    public:
        Sorter(PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>& pattern_matching_machine,
               Core::ConcurrentQueue<boost::filesystem::path>& concurrent_queue,
               const std::string& output_directory);
        virtual ~Sorter();
    protected:
        virtual bool process();
    private:
        void process_job(const Job& job);
    };
    
} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

