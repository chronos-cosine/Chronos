/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Spooler.cpp
 * Author: user
 * 
 * Created on 31 October 2018, 9:16 AM
 */

#include "File/Spooler.h"

#include <experimental/filesystem>
#include <memory>
#include <string>

namespace fs = std::experimental::filesystem;

namespace File {
    
    Spooler::~Spooler() {
    }
   
    Spooler::Spooler(const std::string& directory,
                const std::string& trigger,
                const std::string& busy_extension,
                const std::shared_ptr<Collections::ICollection<std::string>>& collection)
            : Processors::IProcessor(), __directory(directory), __trigger(trigger), 
              __busy_extension(busy_extension), __collection(collection){
    }
   
    bool 
    Spooler::process() {
        bool result = false;
        
        for (const auto& p: fs::directory_iterator(__directory)) {
            if (p.path().extension() == __trigger) {
                if (!result) {
                    result = true;
                }
                
                std::stringstream new_filename;
                new_filename << __directory << p.path().stem().c_str()
                             << __busy_extension;
                
                fs::rename(p, fs::path(new_filename.str()));
                
                __collection->push(new_filename.str());
            }
        }
        
        return result;
    } 
    
} /* namespace File */

