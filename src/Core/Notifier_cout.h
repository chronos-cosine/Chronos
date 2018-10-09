/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier_cout.h
 * Author: user
 *
 * Created on 09 October 2018, 1:57 PM
 */

#ifndef CORE_NOTIFIER_COUT_H
#define CORE_NOTIFIER_COUT_H

#include "Core/INotifier.h"

namespace Core {

    class Notifier_cout : public INotifier {
    public:
        Notifier_cout(); 
        virtual ~Notifier_cout();
        virtual void clear();
        virtual void notify(const char* message);
        virtual void notify(const std::string& message);

    }; /* class Notifier_cout */

} /* namespace Core */

#endif /* CORE_NOTIFIER_COUT_H */

