/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Notifier/Notifiable.h"

/* 
 * File:   NotifyBase.cpp
 * Author: user
 * 
 * Created on 18 October 2018, 8:27 AM
 */


namespace Notifier {
    
    Notifiable::~Notifiable() { }

    Notifiable::Notifiable(const std::shared_ptr<INotifier>& notifier)
            : __notifier(notifier) { }

    void 
    Notifiable::notify(const std::string& message) {
        if (nullptr != __notifier) {
            std::stringstream notification; 
            notification << this << ": " << message;
            
            __notifier->notify(notification);
        }
    }

} /* namespace Notifier */