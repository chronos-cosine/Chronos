/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INotifier.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 10:41 AM
 */

#ifndef NOTIFIER_INOTIFIER_H
#define NOTIFIER_INOTIFIER_H

#include <string>
#include <sstream>

namespace Notifier {
    
    class INotifier {
    public:
        virtual ~INotifier() = default;
        INotifier() = default;
        
        virtual void notify(const char* message) = 0;
        virtual void notify(const std::string& message) = 0;
        virtual void notify(std::stringstream& message) = 0;
        
    }; /* class INotifier */
    
} /* namespace Notifier */

#endif /* NOTIFIER_INOTIFIER_H */

