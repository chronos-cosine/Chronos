/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileNotifier.cpp
 * Author: user
 * 
 * Created on 17 October 2018, 1:25 PM
 */

#include "FileNotifier.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

namespace Notifier {
    
    FileNotifier::~FileNotifier() { }
    
    FileNotifier::FileNotifier(const std::string& file_path)
            : __file_path(file_path), __file_stream(file_path.c_str()) { }

    void 
    FileNotifier::notify(const char* message) {
        std::lock_guard<std::mutex> lock(__mutex);
        
        auto time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        __file_stream << "| " << this 
                      << " | " << std::put_time(std::localtime(&time_t), "%F %T") 
                      << " | " << message 
                      << std::endl;
    }

} /* namespace Notifier */