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

#include "File/JsonDataReader.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Models/Result.h"

#include <boost/property_tree/ptree.hpp>
#include <set>

namespace Sorter {
    namespace Models {
        
        Job& 
        Job::operator<<(const boost::property_tree::ptree& rhs) {
            id = rhs.get<unsigned long long>("id");
            document = rhs.get<std::string>("document");
             
            return *this;
        }
        
        boost::property_tree::ptree&
        Job::operator>>(boost::property_tree::ptree& lhs) const {
            lhs.put("id", id);
            lhs.put("document", document);
            
            if (results.size() > 0) {
                boost::property_tree::ptree ptree_results;
                for (auto& result: results) {
                    boost::property_tree::ptree temp;
                    *result >> temp;
                    ptree_results.push_back(std::make_pair("", std::move(temp)));
                }
                
                lhs.add_child("results", ptree_results);
            }
            
            return lhs;
        }
                
        Job::Job(const fs::path& path) {
            auto temp = File::JsonDataReader<Job>::read(path);
            *this = std::move(*temp);
        }
        
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
            
            return *this;
        }
        
        Job& 
        Job::operator<<(const std::vector<std::string>& rhs) {
            id = std::stoull(rhs[0]);
            document = rhs[1];
            
            return *this;
        }
        
        
    } /* namespace Models */
} /* namespace Sorter */


namespace std {
    
    template<>
    struct hash<Sorter::Models::Job> {
        
        std::size_t 
        operator()(const Sorter::Models::Job& t_job) const {
            return std::hash<unsigned long long>{}(t_job.id);
        }
        
    }; /* struct hash<Sorter::Models::Job> */
        
    template<>
    struct hash<std::shared_ptr<Sorter::Models::Job>> {
        
        std::size_t 
        operator()(const std::shared_ptr<Sorter::Models::Job>& t_job) const {
            if (nullptr == t_job) {
                return 0;
            }
            
            return std::hash<unsigned long long>{}(t_job->id);
        }
        
    }; /* struct hash<std::shared_ptr<Sorter::Models::Job>> */
    
} /* namespace std */