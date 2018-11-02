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

#include "Notifier/LogFileNotifier.h"

#include <thread>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <mutex>

namespace Notifier {
    
    LogFileNotifier::~LogFileNotifier() { }
    
    LogFileNotifier::LogFileNotifier(const unsigned int& reset_minutes, 
                                     const std::string& log_directory) 
            : __reset_minutes(reset_minutes), __log_directory(log_directory) {
        create_file();
                
        __reset_thread = std::make_unique<std::thread>([=] { 
            reset_file(); 
        });
        __reset_thread->detach();
    }
    
    void 
    LogFileNotifier::notify(const char* message) {
        std::lock_guard<std::mutex> lock(__mutex);
        
        __file_notifier->notify(message);
    }
    
    void 
    LogFileNotifier::create_file() {
        std::lock_guard<std::mutex> lock(__mutex);
        
        __reset_time = std::chrono::system_clock::now() + std::chrono::minutes(__reset_minutes);
        auto time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::stringstream filename;
        filename << __log_directory << std::put_time(std::localtime(&time_t), "%Y-%m-%d-%H-%M") << ".log";
        __file_notifier = std::unique_ptr<FileNotifier>(new FileNotifier(filename.str()));
    }
    
    void
    LogFileNotifier::reset_file() {
        while (true) {
            if (__reset_time < std::chrono::system_clock::now()) {
                create_file();
            }
            
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
    }

} /* namespace Notifier */
