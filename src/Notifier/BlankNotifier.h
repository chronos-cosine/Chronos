/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlankNotifier.h
 * Author: user
 *
 * Created on 17 October 2018, 10:39 AM
 */

#ifndef NOTIFIER_BLANKNOTIFIER_H
#define NOTIFIER_BLANKNOTIFIER_H

#include "Notifier/INotifier.h"
 
namespace Notifier {
    
    class BlankNotifier : public INotifier { 
    public:
        BlankNotifier() { }
        virtual ~BlankNotifier() { }
        virtual void notify(const char* message) { }
        virtual void notify(const std::stringstream& message) { }
    public:
        BlankNotifier(BlankNotifier&) = delete;
        BlankNotifier& operator=(BlankNotifier&) = delete;
        BlankNotifier(BlankNotifier&&) = delete;
        BlankNotifier& operator=(BlankNotifier&&) = delete;
    };

} /* namespace Notifier */


#endif /* NOTIFIER_BLANKNOTIFIER_H */

