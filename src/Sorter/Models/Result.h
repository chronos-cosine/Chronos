/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Result.h
 * Author: user
 *
 * Created on 19 November 2018, 8:37 AM
 */

#ifndef SORTER_MODELS_RESULT_H
#define SORTER_MODELS_RESULT_H

#include <boost/optional.hpp>
#include <map>
#include <memory>
#include <set>
#include <string>

namespace Sorter {
    namespace Models {
        
        struct Bin;
        struct Job;
        struct Pattern;
        
        struct Result {
            bool passed;
            std::shared_ptr<Job> job;
            std::shared_ptr<Bin> bin;
            std::map<Pattern, std::set<unsigned long long>> pattern_matches;
            
            bool operator==(const Result& rhs) const noexcept;
            bool operator!=(const Result& rhs) const noexcept;
            bool operator<(const Result& rhs) const noexcept;
            
        }; /* struct Result */
        
    } /* namespace Models */
} /* namespace Sorter */

#endif /* SORTER_MODELS_RESULT_H */

