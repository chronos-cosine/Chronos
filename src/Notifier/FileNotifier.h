/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier/FileNotifier.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
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
        FileNotifier(const FileNotifier&) = delete;
        FileNotifier& operator=(const FileNotifier&) = delete;
    private:
        std::string __file_path;
        std::ofstream __file;
        std::mutex __mutex;
    public:
        virtual ~FileNotifier() = default;
        FileNotifier(const std::string& file_path);
        
        virtual void notify(const std::string& message);
        virtual void notify(std::stringstream& message);
    };
} /* namespace Notifier */
    
#endif /* NOTIFIER_FILENOTIFIER_H */

