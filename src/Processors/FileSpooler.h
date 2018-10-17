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
        std::string __directory;
        std::string __extension;
        std::string __busy_extension;
        Collections::ConcurrentQueue<boost::filesystem::path>& __concurrent_queue;
        std::shared_ptr<Notifier::INotifier> __notifier;
    public:
        FileSpooler(const char* directory, const char* extension,
                    const char* busy_extension,
                    Collections::ConcurrentQueue<boost::filesystem::path>& concurrent_queue,
                    const std::shared_ptr<Notifier::INotifier>& notifier); 
        virtual ~FileSpooler();
    protected:
        virtual bool process();
    public:
        FileSpooler(const FileSpooler&) = delete;
        FileSpooler& operator=(const FileSpooler&) = delete;
        FileSpooler(const FileSpooler&&) = delete;
        FileSpooler& operator=(const FileSpooler&&) = delete;
    };

} /* namespace Processors */

#endif /* CORE_FILESPOOLER_H */

