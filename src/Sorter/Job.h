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

#include <string>
#include <iostream>

namespace Sorter {

    class Job {
    public:
        Job(const unsigned long long& id, const char* document);
        virtual ~Job();
        
        const unsigned long long& get_id() const;
        const std::string& get_document() const;
        
        //friend operators
        friend std::ostream& operator<<(std::ostream& lhs, const Job& rhs);
    private:
        unsigned long long __id;
        std::string __document;
    }; /* class Job */

} /* namespace Sorter */

#endif /* JOB_H */

