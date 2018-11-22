/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NotDataValidator.cpp
 * Author: user
 * 
 * Created on 22 November 2018, 10:24 AM
 */

#include "NotDataValidator.h"

namespace Sorter {
    namespace Services {
    
        bool 
        NotDataValidator::process(const std::shared_ptr<Sorter::Models::Job>& job) {
            return false;
        }
    
    } /* namespace Services */
} /* namespace Sorter */