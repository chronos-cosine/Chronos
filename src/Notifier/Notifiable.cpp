/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier/Notifiable.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 02 November 2018, 4:26 PM
 */

#include "Notifiable.h"

#include <string>
#include <sstream>
#include <memory>

namespace Notifier {
    Notifiable::Notifiable()
        : notifier(std::shared_ptr<Notifier::INotifier>(nullptr)) {
    }
    
    Notifiable::Notifiable(const std::shared_ptr<Notifier::INotifier>& notifier) 
        : notifier(notifier) {
    }
    
    void 
    Notifiable::notify(const std::string& message) {
        if (nullptr != notifier) {
            notifier->notify(message);
        }
    }
    
    void 
    Notifiable::notify(std::stringstream& message) {
        if (nullptr != notifier) {
            notifier->notify(message);
        }
    }
        
} /* namespace Notifier */