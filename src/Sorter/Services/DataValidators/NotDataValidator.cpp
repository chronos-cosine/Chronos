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
        namespace DataValidators {
            
            NotDataValidator::NotDataValidator(
                const std::shared_ptr<Sorter::Data::DataContext>& data_context) 
                    : __data_context(data_context) {
                
            }
        
            void 
            NotDataValidator::process(const std::shared_ptr<Sorter::Models::Job>& job) {
                return;
            }
    
        } /* namespace DataValidators */
    } /* namespace Services */
} /* namespace Sorter */