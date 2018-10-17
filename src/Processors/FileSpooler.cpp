/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Processors/FileSpooler.h"

/* 
 * File:   FileSpooler.cpp
 * Author: user
 * 
 * Created on 12 October 2018, 10:32 AM
 */

#include "Notifier/INotifier.h"
#include "Notifier/BlankNotifier.h"
#include "Collections/ConcurrentQueue.h"

#include <boost/filesystem.hpp>
#include <iostream>
#include <sstream>
#include <memory>

namespace Processors {
    
    FileSpooler::FileSpooler(const char* directory, const char* extension,
                    const char* busy_extension,
                    Collections::ConcurrentQueue<boost::filesystem::path>& concurrent_queue,
                    const std::shared_ptr<Notifier::INotifier>& notifier) 
        : Processors::IProcessor(30, notifier), __directory(directory), __extension(extension), 
          __busy_extension(busy_extension), __concurrent_queue(concurrent_queue),
          __notifier(notifier) { 
    }
 
    FileSpooler::~FileSpooler() { }
    
    bool 
    FileSpooler::process() {
        std::stringstream notification;
        bool result = false;
        boost::filesystem::path directory(__directory);
        boost::filesystem::directory_iterator end_of_directory;
        
        notification << "Looping through directory " << __directory;
        __notifier->notify(notification);
       
        for (boost::filesystem::directory_iterator iterator(directory);
             iterator!= end_of_directory;
             ++iterator) {
            
        
            if (boost::filesystem::is_regular_file(*iterator) 
                && boost::filesystem::extension(*iterator) == __extension) {
                if (!result) {
                    result = true;
                }
                
                std::stringstream new_path; 
                new_path << __directory << (*iterator).path().stem().c_str() << __busy_extension; 
                boost::filesystem::rename(*iterator, boost::filesystem::path(new_path.str()));
                
                notification << "Adding to queue " << new_path.str();
                __notifier->notify(notification);
                __concurrent_queue.push(boost::filesystem::path(new_path.str()));
            }
        }
        
        return result;
    }
}