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
    
    FileSpooler::~FileSpooler() { }
    
    FileSpooler::FileSpooler(const std::string& directory_to_search, 
                             const std::string& trigger_extension,
                             const std::string& busy_extension,
                             Collections::ConcurrentQueue<boost::filesystem::path>& concurrent_queue,
                             const std::shared_ptr<Notifier::INotifier>& notifier,
                             const unsigned int& sleep_time) 
        : Processors::IProcessor(sleep_time, notifier), 
          __directory_to_search(directory_to_search), 
          __trigger_extension(trigger_extension), 
          __busy_extension(busy_extension), 
          __concurrent_queue(concurrent_queue),
          __sleep_time(sleep_time),
          __notifier(notifier) { 
    }
    
    FileSpooler::FileSpooler(const FileSpooler& other)
        : Processors::IProcessor(other.__sleep_time, other.__notifier) ,
          __directory_to_search(other.__directory_to_search), 
          __trigger_extension(other.__trigger_extension), 
          __busy_extension(other.__busy_extension), 
          __concurrent_queue(other.__concurrent_queue),
          __sleep_time(other.__sleep_time),
          __notifier(other.__notifier) {
    }

    bool 
    FileSpooler::process() {
        std::stringstream notification;
        bool result = false;
        boost::filesystem::path directory(__directory_to_search);
        boost::filesystem::directory_iterator end_of_directory;
        
        notification << "Looping through directory " << __directory_to_search;
        notify(notification);
       
        for (boost::filesystem::directory_iterator iterator(directory);
             iterator!= end_of_directory;
             ++iterator) {
            
        
            if (boost::filesystem::is_regular_file(*iterator) 
                && boost::filesystem::extension(*iterator) == __trigger_extension) {
                if (!result) {
                    result = true;
                }
                
                std::stringstream new_path; 
                new_path << __directory_to_search 
                         << (*iterator).path().stem().c_str() 
                         << __busy_extension;
                boost::filesystem::rename(*iterator, boost::filesystem::path(new_path.str()));
                
                notification << "Adding to queue " << new_path.str();
                notify(notification);
                
                __concurrent_queue.push(boost::filesystem::path(new_path.str()));
            }
        }
        
        if (!result) { 
            notification << "Sleeping " << __directory_to_search;
            notify(notification);
        }
        
        return result;
    }
}