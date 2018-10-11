/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JobFileWriter.h
 * Author: user
 *
 * Created on 11 October 2018, 2:00 PM
 */

#ifndef SORTER_JOBFILEWRITER_H
#define SORTER_JOBFILEWRITER_H

#include "Sorter/Job.h"

#include <mutex>

namespace Sorter {

    class JobFileWriter {
    public:
        JobFileWriter(const JobFileWriter&) = delete;
        JobFileWriter& operator=(const JobFileWriter&) = delete;
    public:
        JobFileWriter(); 
        virtual ~JobFileWriter();
        
        void write(const Job& job) const;
    private:
        std::mutex __mutex;
};

} /* namespace Sorter */

#endif /* SORTER_JOBFILEWRITER_H */

