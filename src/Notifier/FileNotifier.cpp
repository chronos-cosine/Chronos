/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier/FileNotifier.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 17 October 2018, 1:25 PM
 */

#include "Notifier/FileNotifier.h" // <-- header >
#include <exception>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

namespace Notifier {
    
    FileNotifier::FileNotifier(const std::string& file_path)
        : __file_path(file_path), 
          __file(file_path) { 
    }

    void 
    FileNotifier::notify(const std::string& message) {
        std::lock_guard<std::mutex> lock(__mutex);
        
        if (!__file.is_open()) {
            throw std::runtime_error("FileNotifier::notify() file is not open");
        }
        
        auto time_t = std::chrono::system_clock::to_time_t(
                        std::chrono::system_clock::now());
        __file  << "| " 
                << this 
                << " | " << std::put_time(std::localtime(&time_t), "%F %T") 
                << " | " << message 
                << std::endl;
    }
    
    void
    FileNotifier::notify(std::stringstream& message) {
        std::lock_guard<std::mutex> lock(__mutex);
        notify(message.str());
        message.str(std::string());
    }

} /* namespace Notifier */