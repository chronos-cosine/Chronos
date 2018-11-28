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

#include "Bin.h"
#include "Job.h"
#include "Pattern.h"
#include "Result.h"

#include <memory>
#include <utility>

namespace Sorter {
    namespace Models {
        
        Result::Result() 
            : passed(true), job(nullptr), bin(nullptr), pattern_matches() {
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
                *pair.first >> ptree_pattern;
                ptree_pattern_matches.add_child("pattern", std::move(ptree_pattern));
                
                for (auto& index: pair.second) {
                    ptree_positions.add("", index);
                }
                ptree_pattern_matches.add_child("positions", std::move(ptree_positions));
            } 
            lhs.add_child("pattern_matches", std::move(ptree_pattern_matches));
            
            return lhs;
        }
        
    } /* namespace Models */
} /* namespace Sorter */