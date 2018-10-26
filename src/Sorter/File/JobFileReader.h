/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JobFileReader.h
 * Author: user
 *
 * Created on 10 October 2018, 9:15 AM
 */

#ifndef SORTER_JOBFILEREADER_H
#define SORTER_JOBFILEREADER_H

#include "Sorter/Job.h"
#include <memory>

namespace Sorter {

    class JobFileReader {
    public:
        virtual ~JobFileReader();
        JobFileReader();
        JobFileReader(JobFileReader&&) = default;
        JobFileReader& operator=(JobFileReader&&) = default;
        
        std::unique_ptr<Job> read(const std::string& filename) const;
    };

} /* namespace Sorter */

#endif /* JOBFILEREADER_H */
