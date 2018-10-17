/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INotifier.h
 * Author: user
 *
 * Created on 17 October 2018, 10:15 AM
 */

#ifndef NOTIFIER_INOTIFIER_H
#define NOTIFIER_INOTIFIER_H

#include <iostream>
#include <string>
#include <sstream>

namespace Notifier {
    
    class INotifier {
    public:
        INotifier() { }
        virtual ~INotifier() { };
        virtual void notify(const char* message) = 0; 
        
        virtual void notify(std::stringstream& message) {  
            notify(message.str().c_str());
            message.str(std::string());
        } 
    public:
        INotifier(INotifier&) = delete;
        INotifier& operator=(INotifier&) = delete;
        INotifier(INotifier&&) = delete;
        INotifier& operator=(INotifier&&) = delete;
    };
    
} /* namespace Notifier */


#endif /* NOTIFIER_INOTIFIER_H */

