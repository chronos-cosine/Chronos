/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier_cout.cpp
 * Author: user
 * 
 * Created on 09 October 2018, 1:57 PM
 */

#include "Core/Notifier_cout.h"

#include <iostream>

namespace Core {

    Notifier_cout::Notifier_cout() { }

    Notifier_cout::~Notifier_cout() { }

    void 
    Notifier_cout::clear() {
        std::cout << std::flush;
    }

    void 
    Notifier_cout::notify(const char* message) { 
        std::cout << message << std::endl;
    }

    void 
    Notifier_cout::notify(const std::string& message) { 
        std::cout << message << std::endl;
    }
    
} /* namespace Core */