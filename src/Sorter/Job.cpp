/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter/Job.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 31 October 2018, 10:52 PM
 */

#include "Job.h"

#include "File/JsonDataWriter.h"
#include "File/JsonDataReader.h"

#include <memory>

namespace Sorter {
    
    bool 
    Job::operator<(const Job& rhs) const {
        return id < rhs.id;
    }
    
    bool 
    Job::operator==(const Job& rhs) const {
        return id == rhs.id;
    }
    
    bool 
    Job::operator!=(const Job& rhs) const {
        return !(*this == rhs);
    }
    
    Job& 
    Job::operator<<(const boost::property_tree::ptree& rhs) {
        id = rhs.get<unsigned long long>("id");
        document = rhs.get<std::string>("document");
        
        return *this;
    }

    std::string::const_iterator 
    Job::begin() const {
        return document.begin();
    }
    
    std::string::const_iterator 
    Job::end() const {
        return document.end();
    }
    
    Job::Job(const fs::path& path) {
        *this = path;
    }
    
    Job& 
    Job::operator=(const fs::path& path) {
        *this = std::move(*File::JsonDataReader<Job>::read(path)); 
        return *this;
    }
    
    //friend operators
    bool
    operator<(const std::shared_ptr<Job>& lhs, const std::shared_ptr<Job>& rhs) {
        if (nullptr == lhs && nullptr == rhs) {
            return false;
        } else if (nullptr == lhs) {
            return true;
        } else if (nullptr == rhs) {
            return false;
        }
        
        return *lhs < *rhs;
    }
    
    bool
    operator==(const std::shared_ptr<Job>& lhs, const std::shared_ptr<Job>& rhs) {
        if (nullptr == lhs && nullptr == rhs) {
            return true;
        } else if (nullptr == lhs || nullptr == rhs) {
            return false;
        }
        
        return *lhs == *rhs;
    }
    
    bool
    operator!=(const std::shared_ptr<Job>& lhs, const std::shared_ptr<Job>& rhs) {
        return !(lhs == rhs);
    }

    
    std::ostream& 
    operator<<(std::ostream& lhs, const Job& rhs) {
        File::JsonDataWriter<Job>::write(lhs, rhs);
        return lhs;
    }
        
    boost::property_tree::ptree& 
    operator<<(boost::property_tree::ptree& lhs, const Job& rhs) {
        lhs.put("id", rhs.id);
        lhs.put("document", rhs.document);
        
        return lhs;
    }

} /* namespace Sorter */

namespace std {
    template <>
    struct hash<Sorter::Job> {
        std::size_t 
        operator()(const Sorter::Job& job) const {
            return std::hash<unsigned long long>{}(job.id);
        }
    };
    
    template <>
    struct hash<std::shared_ptr<Sorter::Job>> {
        std::size_t 
        operator()(const std::shared_ptr<Sorter::Job>& job) const {
            if (nullptr == job)
            {
                return 0;
            }
            return std::hash<unsigned long long>{}(job->id);
        }
    };
}