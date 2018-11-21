/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IStep.h
 * Author: user
 *
 * Created on 20 November 2018, 10:56 AM
 */

#ifndef SORTER_STEPS_ISTEP_H
#define SORTER_STEPS_ISTEP_H

#include "Sorter/Models/Job.h"

namespace Sorter {
    namespace Steps {
        
        class IStep {
        public:
            virtual ~IStep() = default;
            IStep() = default;
            
            virtual bool process(const Sorter::Models::Job& job) = 0;
            
        }; /* class IStep */
        
    } /* namespace Steps */
} /* namespace Sorter */

#endif /* SORTER_STEPS_ISTEP_H */

