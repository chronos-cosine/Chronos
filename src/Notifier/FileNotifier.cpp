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

namespace Notifier {
    
    FileNotifier::FileNotifier(const std::string& file_path)
            : __file_path(file_path), __file_stream(file_path.c_str()) {
    }

    FileNotifier::~FileNotifier() { }
    
    void 
    FileNotifier::notify(const char* message) {
        std::lock_guard<std::mutex> lock(__mutex);
        __file_stream << message << std::endl;
    }

} /* namespace Notifier */