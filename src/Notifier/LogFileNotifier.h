/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier/LogFileNotifier.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 18 October 2018, 10:52 PM
 */

#ifndef NOTIFIER_LOGFILENOTIFIER_H
#define NOTIFIER_LOGFILENOTIFIER_H

#include "Notifier/FileNotifier.h"
#include "Notifier/INotifier.h"
#include "Processors/ProcessorBase.h"
#include "INotifier.h"

#include <chrono>
#include <memory>
#include <string>
#include <thread>

namespace Notifier {
    
    class LogFileNotifier : public INotifier {
        LogFileNotifier(const LogFileNotifier&) = delete;
        LogFileNotifier& operator=(const LogFileNotifier&) = delete;
    public:
        virtual ~LogFileNotifier() = default;
        LogFileNotifier(const std::chrono::minutes& reset_time, 
                        const std::string& log_directory);
        
        virtual void notify(const std::string& message);
        virtual void notify(std::stringstream& message);
    private:
        std::string __log_directory;
        std::chrono::minutes __reset_time;
        std::mutex __mutex;
        std::unique_ptr<FileNotifier> __file_notifier;
        std::chrono::system_clock::time_point __log_file_recycle_time_point;
        std::thread __log_file_recycle_thread;
    private:
        void create_file();
        void reset_file();
    };

} /* namespace Notifier */



#endif /* NOTIFIER_LOGFILENOTIFIER_H */

