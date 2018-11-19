/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Job.cpp
 * Author: user
 * 
 * Created on 19 November 2018, 8:27 AM
 */

#include "Job.h"


namespace Sorter {
    namespace Models {
        
        std::string::const_iterator 
        Job::begin() const {
            return document.begin();
        }
        
        std::string::const_iterator 
        Job::end() const {
            return document.end();
        }
        
        bool 
        Job::operator==(const Job& rhs) const noexcept {
            return id == rhs.id;
        }
        
        bool 
        Job::operator!=(const Job& rhs) const noexcept {
            return !(*this == rhs);
        }
        
        bool 
        Job::operator<(const Job& rhs) const noexcept {
            return id < rhs.id;
        }
        
        Job& 
        Job::operator=(const Job& rhs) {
            id = rhs.id;
            document = rhs.document;
        }
        
        Job& 
        Job::operator<<(const std::vector<std::string>& rhs) {
            id = std::stoull(rhs[0]);
            document = rhs[1];
        }
          
    } /* namespace Models */
} /* namespace Sorter */
