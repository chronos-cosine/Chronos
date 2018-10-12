/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResultFileWriter.h
 * Author: user
 *
 * Created on 10 October 2018, 11:00 AM
 */

#ifndef SORTER_RESULTFILEWRITER_H
#define SORTER_RESULTFILEWRITER_H

#include "Sorter/Job.h"
#include "Sorter/Pattern.h"

#include <map> 
#include <memory>
#include <mutex>
#include <set>
#include <string>

namespace Sorter {

    class ResultFileWriter {
    public:
        ResultFileWriter(const ResultFileWriter&) = delete;
        ResultFileWriter& operator=(const ResultFileWriter&) = delete;
    public:
        ResultFileWriter();
        virtual ~ResultFileWriter();
        
        void write(const Job& job, 
                   const std::map<std::shared_ptr<Pattern>, std::set<unsigned long long>>& matches);
    private:
        std::mutex __mutex;

    }; /* class ResultFileWriter */

} /* namespace Sorter */

#endif /* RESULTFILEWRITER_H */

