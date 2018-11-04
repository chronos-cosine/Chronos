/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File/Spooler.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 31 October 2018, 10:52 PM
 */

#include "File/Spooler.h"

#include <chrono>
#include <experimental/filesystem>
#include <memory>
#include <string>

namespace fs = std::experimental::filesystem;

namespace File {
    
    Spooler::Spooler(const std::string& directory,
                     const std::string& trigger,
                     const std::string& busy_extension,
                     const std::chrono::seconds& sleep_time,
                     const std::shared_ptr<Collections::ICollection<std::string>>& collection)
            : Processors::ProcessorBase(sleep_time), 
              __directory(directory), 
              __trigger(trigger), 
              __busy_extension(busy_extension), 
              __collection(collection) {
    }
    
    bool 
    Spooler::process() {
        if (!fs::exists(__directory)) {
            throw std::runtime_error("Spooler::process() directory does not exist");
        }
        
        bool result = false;
        for (const auto& item: fs::directory_iterator(__directory)) {
            if (item.path().extension() == __trigger) {
                if (!result) {
                    result = true;
                }
                
                std::string new_filename = __directory + 
                                            item.path().stem().c_str() +
                                            __busy_extension;
                
                try {
                    fs::rename(item, new_filename);
                } catch (const fs::filesystem_error& e) {
                    return false;
                }
                
                __collection->push(new_filename);
            }
        }
        
        return result;
    } 
    
} /* namespace File */

