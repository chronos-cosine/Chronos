/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileSpooler.cpp
 * Author: user
 * 
 * Created on 12 October 2018, 10:32 AM
 */

#include "Core/FileSpooler.h"

#include <boost/filesystem.hpp>
#include <sstream>

namespace Core {

    FileSpooler::FileSpooler(const char* directory, const char* extension,
                    Core::ConcurrentQueue<boost::filesystem::path>& concurrent_queue) 
        : Core::IProcessor(5), __directory(directory), __extension(extension), 
          __concurrent_queue(concurrent_queue) { }
 
    FileSpooler::~FileSpooler() { }
    
    bool 
    FileSpooler::process() {
        bool result = false;
        boost::filesystem::path directory(__directory);
        boost::filesystem::directory_iterator end_of_directory;
        
        for (boost::filesystem::directory_iterator iterator(directory);
             iterator!= end_of_directory;
             ++iterator) { 
            if (boost::filesystem::is_regular_file(*iterator) 
                && boost::filesystem::extension(*iterator) == __extension) {
                if (!result) {
                    result = true;
                }
                std::stringstream stringstream;
                stringstream << (*iterator).path().string() << ".busy";
                
                boost::filesystem::path new_path(stringstream.str());
                boost::filesystem::rename(*iterator, new_path);
                
                __concurrent_queue.push(new_path);
            }
        }
        
        return result;
    }
}