/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Job.h
 * Author: user
 *
 * Created on 10 October 2018, 8:52 AM
 */

#ifndef SORTER_JOB_H
#define SORTER_JOB_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <iostream>
#include <mutex>

namespace Sorter {

    class Job {
    private:
        unsigned long long __id;
        std::string __document;
        std::string __filename;
        std::mutex __mutex;
    public:
        struct Hasher {
            std::size_t operator()(const Job& job) const noexcept {
                return std::hash<unsigned long long>{}(job.__id);
            }
        };
    public:
        Job(const unsigned long long& id, const std::string& document, const std::string& filename);
        virtual ~Job();
        
        const unsigned long long& get_id() const;
        const std::string& get_document() const;
        const std::string& get_filename() const;
        
        std::string::const_iterator begin() const; 
        std::string::const_iterator end() const;
        
        //operators 
        virtual bool operator==(const Job& rhs) const;
        virtual bool operator!=(const Job& rhs) const;
        virtual bool operator<(const Job& rhs) const;
        virtual bool operator>(const Job& rhs) const;
        
        //friend operators
        friend boost::property_tree::ptree& operator<<(boost::property_tree::ptree& lhs, const Job& rhs);
        friend std::ostream& operator<<(std::ostream& lhs, const Job& rhs); 
        friend bool operator<(const std::shared_ptr<Job>& lhs, const std::shared_ptr<Job>& rhs);
        friend bool operator>(const std::shared_ptr<Job>& lhs, const std::shared_ptr<Job>& rhs);
        friend bool operator==(const std::shared_ptr<Job>& lhs, const std::shared_ptr<Job>& rhs);
        friend bool operator!=(const std::shared_ptr<Job>& lhs, const std::shared_ptr<Job>& rhs);
    public:
        Job(const Job&) = delete;
        Job& operator=(Job&) = delete;
        Job(Job&&) = delete;
        Job& operator=(Job&&) = delete;
        
    }; /* class Job */

} /* namespace Sorter */

#endif /* JOB_H */

