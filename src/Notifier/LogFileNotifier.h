/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LogFileNotifier.h
 * Author: user
 *
 * Created on 18 October 2018, 8:08 AM
 */

#ifndef NOTIFIER_LOGFILENOTIFIER_H
#define NOTIFIER_LOGFILENOTIFIER_H

#include "Notifier/FileNotifier.h"
#include "Notifier/INotifier.h"

#include <chrono>
#include <fstream>
#include <mutex>
#include <memory>
#include <string>
#include <thread>

namespace Notifier {
    
    class LogFileNotifier : public INotifier {
    private:
        std::chrono::system_clock::time_point __reset_time;
        unsigned short __reset_minutes; 
        bool __is_running;
        std::string __log_directory;
        std::unique_ptr<FileNotifier> __file_notifier;
        std::mutex __mutex;
        std::unique_ptr<std::thread> __reset_thread;
    public:
        virtual ~LogFileNotifier();
        LogFileNotifier(const unsigned int& reset_minutes, const std::string& log_directory);
        
        virtual void notify(const char* message);
    private:
        void reset_file();
        void create_file();

    };

} /* namespace Notifier */



#endif /* NOTIFIER_LOGFILENOTIFIER_H */

