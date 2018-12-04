/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Job.cpp
 * Author: user
 * 
 * Created on 04 December 2018, 10:36 AM
 */

#include "Pdf/Splitter/Models/Job.h"
#include "File/JsonDataReader.h"

namespace Pdf {
    namespace Splitter { 
        namespace Models { 

            Job& 
            Job::operator<<(const boost::property_tree::ptree& rhs) {
                id = rhs.get<unsigned long long>("id");
                filename = rhs.get<std::string>("filename");

                return *this;
            }

            boost::property_tree::ptree&
            Job::operator>>(boost::property_tree::ptree& lhs) const {
                lhs.put("id", id);
                lhs.put("filename", filename);

                return lhs;
            }

            Job::Job(const fs::path& path) {
                auto temp = File::JsonDataReader<Job>::read(path);
                *this = std::move(*temp);
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
                filename = rhs.filename;

                return *this;
            }

            Job& 
            Job::operator<<(const std::vector<std::string>& rhs) {
                id = std::stoull(rhs[0]);
                filename = rhs[1];

                return *this;
            }

        
        } /* namespace Models */
    } /* namespace Splitter */
} /* namespace Pdf */


namespace std {
    
    template<>
    struct hash<Pdf::Splitter::Models::Job> {
        
        std::size_t 
        operator()(const Pdf::Splitter::Models::Job& t_job) const {
            return std::hash<unsigned long long>{}(t_job.id);
        }
        
    }; /* struct hash<Sorter::Models::Job> */
         
} /* namespace std */