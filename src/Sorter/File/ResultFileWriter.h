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
#include "Notifier/INotifier.h"

#include <map> 
#include <memory>
#include <mutex>
#include <set>
#include <string>

namespace Sorter {

    class ResultFileWriter {
    private:
        std::shared_ptr<Notifier::INotifier> __notifier;
        std::string __completed_extension;
    public:
        ResultFileWriter(const std::string& completed_extension,
                         const std::shared_ptr<Notifier::INotifier>& notifier);
        virtual ~ResultFileWriter();
        
        void write(const Job& job,
                   const std::map<std::shared_ptr<Pattern>, std::set<unsigned long long>>& patterns,
                   const std::set<std::shared_ptr<Bin>>& bins,
                   const std::string& output_directory);
    private:
        boost::property_tree::ptree read_job_file(const Job& job);
    public:
        ResultFileWriter(const ResultFileWriter&) = delete;
        ResultFileWriter& operator=(const ResultFileWriter&) = delete;

    }; /* class ResultFileWriter */

} /* namespace Sorter */

#endif /* RESULTFILEWRITER_H */

