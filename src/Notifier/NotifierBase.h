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

#ifndef NOTIFIER_NOTIFIERBASE_H
#define NOTIFIER_NOTIFIERBASE_H

#include "Notifier/INotifier.h"

#include <iostream>
#include <string>
#include <sstream>

namespace Notifier {
    
    class NotifierBase : public INotifier {
    public:
        virtual ~NotifierBase() = default;
        NotifierBase() = default;
        
        virtual void notify(const std::string& message);
        virtual void notify(std::stringstream& message);
    };
    
} /* namespace Notifier */

#endif /* NOTIFIER_NOTIFIERBASE_H */

