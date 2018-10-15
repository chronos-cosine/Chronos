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

#include "Core/IProcessor.h"
#include "Core/ConcurrentQueue.h"

#include <boost/filesystem/path.hpp>
#include <memory>
#include <string>

namespace Core {

    class FileSpooler : public Core::IProcessor {
    public:
        FileSpooler(const FileSpooler&) = delete;
        FileSpooler& operator=(const FileSpooler&) = delete;
    public:
        FileSpooler(const char* directory, const char* extension,
                    Core::ConcurrentQueue<boost::filesystem::path>& concurrent_queue); 
        virtual ~FileSpooler();
    protected:
        virtual bool process();
    private:
        std::string __directory;
        std::string __extension;
        Core::ConcurrentQueue<boost::filesystem::path>& __concurrent_queue;
    };

} /* namespace Core */

#endif /* CORE_FILESPOOLER_H */

