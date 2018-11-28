/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier/LogFileNotifier.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 18 October 2018, 10:52 PM
 */

#include "Notifier/LogFileNotifier.h" // <-- header >
#include "Notifier/FileNotifier.h"

#include <chrono>
#include <exception>
#include <experimental/filesystem>
#include <iomanip>
#include <memory>
#include <string>
#include <sstream>

namespace fs = std::experimental::filesystem;

namespace Notifier {
    
    LogFileNotifier::LogFileNotifier(const std::chrono::minutes& reset_time, 
                                     const std::string& log_directory)
            : __reset_time(reset_time), __log_directory(log_directory),
              __log_file_recycle_time_point(std::chrono::system_clock::now() 
                                            - __reset_time) {
        if (!fs::exists(log_directory)) {
            throw std::runtime_error("LogFileNotifier::LogFileNotifier() log directory does not exist");
        }
        create_file();
        
        __log_file_recycle_thread = std::thread([=] { 
            reset_file(); 
        });
        __log_file_recycle_thread.detach();
    }
    
    void 
    LogFileNotifier::create_file() {
        std::lock_guard<std::mutex> lock(__mutex);
        
        __log_file_recycle_time_point = std::chrono::system_clock::now() 
                                        + __reset_time;
        auto time_t = std::chrono::system_clock::to_time_t(
                        std::chrono::system_clock::now());
        std::stringstream filename;
        filename << __log_directory 
                 << std::put_time(std::localtime(&time_t), "%Y-%m-%d-%H-%M") 
                 << ".log";
        __file_notifier = std::make_unique<FileNotifier>(filename.str());
    }
    
    void
    LogFileNotifier::reset_file() {
        while (true) {
            if (__log_file_recycle_time_point 
                    < std::chrono::system_clock::now()) {
                create_file();
            }
            
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
    }

    void 
    LogFileNotifier::notify(const std::string& message) {
        std::lock_guard<std::mutex> lock(__mutex);
        
        __file_notifier->notify(message);
    }
    
    void
    LogFileNotifier::notify(std::stringstream& message) {
        std::lock_guard<std::mutex> lock(__mutex);
        notify(message.str());
        message.str(std::string());
    }

} /* namespace Notifier */
