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

#include <boost/property_tree/ptree.hpp>
#include <experimental/filesystem>
#include <memory>
#include <string>
#include <vector>
#include <set>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    namespace Models {
        struct Result;
        
        struct Job {
            unsigned long long id;
            std::string document;
            std::set<std::shared_ptr<Result>> results;
            
            Job() = default;
            Job(const fs::path& path);
            
            std::string::const_iterator begin() const;
            std::string::const_iterator end() const;
            
            bool operator==(const Job& rhs) const noexcept;
            bool operator!=(const Job& rhs) const noexcept;
            bool operator<(const Job& rhs) const noexcept;
            Job& operator=(const Job& rhs);
            Job& operator<<(const std::vector<std::string>& rhs);
            Job& operator<<(const boost::property_tree::ptree& rhs);
            
            boost::property_tree::ptree& 
            operator>>(boost::property_tree::ptree& lhs) const;
            
        }; /* struct Job */
        
    } /* namespace Models */
} /* namespace Sorter */

#endif /* SORTER_MODELS_JOB_H */

