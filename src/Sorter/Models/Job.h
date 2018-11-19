/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Job.h
 * Author: user
 *
 * Created on 19 November 2018, 8:27 AM
 */

#ifndef SORTER_MODELS_JOB_H
#define SORTER_MODELS_JOB_H

#include <memory>
#include <string>
#include <vector>

namespace Sorter {
    namespace Models {
        
        struct Job {
            unsigned long long id;
            std::string document;
            
            std::string::const_iterator begin() const;
            std::string::const_iterator end() const;
            
            bool operator==(const Job& rhs) const noexcept;
            bool operator!=(const Job& rhs) const noexcept;
            bool operator<(const Job& rhs) const noexcept;
            Job& operator=(const Job& rhs);
            Job& operator<<(const std::vector<std::string>& rhs);
            
        }; /* struct Job */
        
    } /* namespace Models */
} /* namespace Sorter */

#endif /* SORTER_MODELS_JOB_H */

