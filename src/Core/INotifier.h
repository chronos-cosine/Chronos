/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INotifier.h
 * Author: user
 *
 * Created on 09 October 2018, 1:16 PM
 */

#ifndef CORE_INOTIFIER_H
#define CORE_INOTIFIER_H

#include <string>

namespace Core { 

    class INotifier {
    public:
        virtual void clear() = 0;
        virtual void notify(const char* message) = 0;
        virtual void notify(const std::string& message) = 0;

    }; /* class INotifier */

} /* namespace Core */

#endif /* CORE_INOTIFIER_H */

