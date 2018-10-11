/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.h
 * Author: user
 *
 * Created on 05 October 2018, 8:53 AM
 */

#ifndef SORTER_SORTER_H
#define SORTER_SORTER_H

namespace Sorter {
/*
    class Sorter : public Core::IProcessor {
    private:
        struct match_found_functor {
            Sorter* __sorter;
            void operator()(void* sender , 
                            const unsigned long long& position,
                            PatternMatcher::IPattern* input ,
                            const std::set<PatternMatcher::IPattern*>& patterns) const {
                for (PatternMatcher::IPattern* p: patterns) {
                    Pattern* pattern = dynamic_cast<Pattern*>(p); 
                    __sorter->__matches[input][pattern].insert(position);
                }
            }
        };
    public:
        Sorter(const Sorter&) = delete;
        Sorter& operator=(const Sorter&) = delete;
    public:
        Sorter(const char* pattern_file, const char* bin_file, const char* job_path);
        virtual ~Sorter();
    private: 
        void initialise_sorter();
        void link_pattern_bin();
        template <typename T> std::set<T*> map_values_to_set(const std::map<unsigned long long, T*> map);
    protected:
        virtual bool process();
    private:
        std::string __job_path;
        PatternFileReader __pattern_file_reader;
        BinFileReader __bin_file_reader;
        MemoryManagement __memory_management;
        std::map<unsigned long long, Bin*> __bins;
        std::map<unsigned long long, PatternMatcher::IPattern*> __patterns;
        PatternMatcher::PatternMatchingMachine __pattern_matching_machine;
        JobFileReader __job_file_reader;
        ResultFileWriter __result_file_writer;
        Sorter::match_found_functor __match_found_functor;
        std::map<PatternMatcher::IPattern*, std::map<Pattern*, std::set<unsigned long long>>> __matches;
        
    };  
    
    template <typename T>
    std::set<T*>
    Sorter::map_values_to_set(const std::map<unsigned long long, T*> map) {
        std::set<T*> set;
        for (const auto& pair: map) {
            set.insert(pair.second);
        }
        
        return set;
    }
     */
} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

