/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier/INotifier.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 17 October 2018, 10:52 PM
 */


#include "Notifier/NotifierBase.h" // <-- Header -->

#include <string>
#include <sstream>

namespace Notifier {
    
    void 
    NotifierBase::notify(const std::string& message) {  
        notify(message.c_str());
    }
    
    void
    NotifierBase::notify(std::stringstream& message) {  
        notify(message.str().c_str());
        message.str(std::string());
    }
    
} /* namespace Notifier */
