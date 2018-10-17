/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Notifier/CoutNotifier.h"

/* 
 * File:   CoutNotifier.cpp
 * Author: user
 * 
 * Created on 17 October 2018, 10:34 AM
 */

#include <sstream>
#include <iostream>

namespace Notifier {
    
    CoutNotifier::CoutNotifier() { }

    CoutNotifier::~CoutNotifier() { }
    
    void 
    CoutNotifier::notify(const char* message) {
        std::lock_guard<std::mutex> lock(__mutex);
        std::cout << message << std::endl;
    }
    
} /* namespace Notifier */
