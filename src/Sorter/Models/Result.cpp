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

namespace Sorter {
    namespace Models {
        
        boost::property_tree::ptree&
        operator<<(boost::property_tree::ptree& lhs, const Result& result) { 
        }
        
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
        
    } /* namespace Models */
} /* namespace Sorter */