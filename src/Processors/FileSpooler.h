/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileSpooler.h
 * Author: user
 *
 * Created on 12 October 2018, 10:32 AM
 */

#ifndef CORE_FILESPOOLER_H
#define CORE_FILESPOOLER_H

#include "Processors/IProcessor.h"
#include "Collections/ConcurrentQueue.h"
#include "Notifier/INotifier.h"

#include <boost/filesystem/path.hpp>
#include <memory>
#include <string>

namespace Processors {
    
    class FileSpooler : public Processors::IProcessor {
    private:
        std::string __directory_to_search;
        std::string __trigger_extension;
        std::string __busy_extension;
        Collections::ConcurrentQueue<boost::filesystem::path>& __concurrent_queue;
        unsigned int __sleep_time;
        std::shared_ptr<Notifier::INotifier> __notifier;
    public:
        virtual ~FileSpooler();
        FileSpooler(const std::string& directory_to_search, 
                    const std::string& trigger_extension,
                    const std::string& busy_extension,
                    Collections::ConcurrentQueue<boost::filesystem::path>& concurrent_queue,
                    const std::shared_ptr<Notifier::INotifier>& notifier,
                    const unsigned int& sleep_time);
        FileSpooler(const FileSpooler& other);
    protected:
        virtual bool process();
    };

} /* namespace Processors */

#endif /* CORE_FILESPOOLER_H */

