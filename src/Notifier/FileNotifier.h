/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileNotifier.h
 * Author: user
 *
 * Created on 17 October 2018, 1:25 PM
 */

#ifndef NOTIFIER_FILENOTIFIER_H
#define NOTIFIER_FILENOTIFIER_H

#include "Notifier/INotifier.h"
#include <fstream>
#include <mutex>

namespace Notifier {
    
    class FileNotifier : public INotifier {
    private:
        std::string __file_path;
        std::ofstream __file_stream;
        std::mutex __mutex;
    public:
        FileNotifier(const std::string& file_path); 
        virtual ~FileNotifier();
        
        virtual void notify(const char* message);
    public:
        FileNotifier(FileNotifier&) = delete;
        FileNotifier& operator=(FileNotifier&) = delete;
        FileNotifier(FileNotifier&&) = delete;
        FileNotifier& operator=(FileNotifier&&) = delete;
    };
} /* namespace Notifier */
    
#endif /* NOTIFIER_FILENOTIFIER_H */
