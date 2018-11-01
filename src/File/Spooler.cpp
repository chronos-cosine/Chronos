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
    } /* ~Spooler() */
   
    Spooler::Spooler(const std::string& directory,
                const std::string& trigger,
                const std::shared_ptr<Collections::ICollection<std::string>>& collection)
            : Processors::IProcessor(), __directory(directory), __trigger(trigger), 
              __collection(collection){
    } /* Spooler() */
   
    bool 
    Spooler::process() {        
        for (const auto& p: fs::directory_iterator(__directory)) {
            if (p.path().extension() == __trigger) {
                __collection->push(p.path().string());
            }
        }
        
        return false;
    } /* bool process() */
    
} /* namespace File */

