/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier/CoutNotifier.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 17 October 2018, 10:52 PM
 */

#include "Notifier/CoutNotifier.h"

#include <sstream>
#include <iostream>

namespace Notifier {
    
    CoutNotifier::~CoutNotifier() { }
    
    CoutNotifier::CoutNotifier() { }

    void 
    CoutNotifier::notify(const char* message) {
        std::lock_guard<std::mutex> lock(__mutex);
        
        std::cout << this << ": " << message << std::endl;
    }
    
} /* namespace Notifier */
