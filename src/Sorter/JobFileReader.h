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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace Sorter {

    class JobFileReader {
    public:
        JobFileReader();
        virtual ~JobFileReader();
        
        Job* read(const char* job_file_name);
    private:
        // void print(boost::property_tree::ptree const& pt);
    };

} /* namespace Sorter */

#endif /* JOBFILEREADER_H */

