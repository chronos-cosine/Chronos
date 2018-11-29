/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Result.cpp
 * Author: user
 * 
 * Created on 19 November 2018, 8:37 AM
 */

#include "Sorter/Models/Bin.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Models/Pattern.h"
#include "Sorter/Models/Result.h"

#include <boost/functional/hash.hpp>
#include <memory>

namespace Sorter {
    namespace Models {
        
        Result::Result() 
          : passed(true), 
            job(nullptr), 
            bin(nullptr) {
        }
          
        bool 
        Result::operator==(const Result& rhs) const noexcept {
            return job->id == rhs.job->id
                   && bin->id == rhs.bin->id;
        }
        
        bool 
        Result::operator!=(const Result& rhs) const noexcept {
            return !(*this == rhs);
        }
        
        bool 
        Result::operator<(const Result& rhs) const noexcept {
            if (job->id == rhs.job->id) {
                return bin->id < rhs.bin->id;
            } else {
                return job->id < rhs.job->id;
            }
        }
        
        boost::property_tree::ptree& 
        Result::operator>>(boost::property_tree::ptree& lhs) const {
            lhs.put("passed", passed);
            if (job != nullptr) {
                lhs.put("job_id", job->id);
            }
            
            if (bin != nullptr) {
                lhs.put("bin_id", bin->id);
            }
            
            boost::property_tree::ptree ptree_pattern_matches;
            for (auto& pair: pattern_matches) {
                boost::property_tree::ptree ptree_pattern;
                boost::property_tree::ptree ptree_positions;
                if (nullptr != pair.first) {
                    *pair.first >> ptree_pattern;
                    ptree_pattern_matches.add_child("pattern", std::move(ptree_pattern));

                    for (unsigned long long index: pair.second) {
                        boost::property_tree::ptree item;
                        item.put("", index);
                        ptree_positions.push_back(std::make_pair("", std::move(item)));
                    }
                    ptree_pattern_matches.add_child("positions", std::move(ptree_positions));
                }
            } 
            lhs.add_child("pattern_matches", std::move(ptree_pattern_matches));
            
            return lhs;
        }
        
        bool
        operator==(const std::shared_ptr<Result>& lhs, 
                   const std::shared_ptr<Result>& rhs) {
            if (lhs == nullptr
                && rhs == nullptr) {
                return true;
            } else if (lhs == nullptr
                || rhs == nullptr) {
                return false;
            }
            
            return (*lhs == *rhs);
        }
        
        bool
        operator!=(const std::shared_ptr<Result>& lhs, 
                   const std::shared_ptr<Result>& rhs) {
            return !(lhs == rhs);
        }
        
        bool
        operator<(const std::shared_ptr<Result>& lhs, 
                  const std::shared_ptr<Result>& rhs) {
            if (lhs == nullptr
                && rhs == nullptr) {
                return false;
            } else if (lhs == nullptr) {
                return true;
            } else if (rhs == nullptr) {
                return false;
            }
            
            return (*lhs < *rhs);
        }
        
    } /* namespace Models */
} /* namespace Sorter */


namespace std {
    
    template<>
    struct hash<Sorter::Models::Result> {
        
        std::size_t 
        operator()(const Sorter::Models::Result& t_result) const {
            std::size_t seed = 0;
            
            if (nullptr != t_result.bin) {
                boost::hash_combine(seed, t_result.bin->id);
            }
            
            if (nullptr != t_result.job) {
                boost::hash_combine(seed, t_result.job->id);
            }
                
            return seed; 
        }
        
    }; /* struct hash<Sorter::Models::Result> */
    
} /* namespace std */
