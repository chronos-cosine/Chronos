/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Job.h
 * Author: user
 *
 * Created on 04 December 2018, 10:36 AM
 */

#ifndef PDF_SPLITTER_MODELS_JOB_H
#define PDF_SPLITTER_MODELS_JOB_H

#include <boost/property_tree/ptree.hpp>
#include <experimental/filesystem>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::experimental::filesystem;

namespace Pdf {
    namespace Splitter { 
        namespace Models { 
            
            struct Job {
                unsigned long long id;
                std::string filename;
                
                Job() = default;
                Job(const fs::path& path);

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
    } /* namespace Splitter */
} /* namespace Pdf */

#endif /* PDF_SPLITTER_MODELS_JOB_H */

