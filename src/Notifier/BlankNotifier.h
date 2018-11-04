/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier/BlankNotifier.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 17 October 2018, 10:52 PM
 */

#ifndef NOTIFIER_BLANKNOTIFIER_H
#define NOTIFIER_BLANKNOTIFIER_H

#include "Notifier/INotifier.h"
 
namespace Notifier {
    
    class BlankNotifier : public INotifier { 
    public:
        virtual ~BlankNotifier() = default;
        BlankNotifier() = default;
        
        virtual void notify(const char* message) { }
        virtual void notify(const std::string& message) { };
        virtual void notify(const std::stringstream& message) { }
    };

} /* namespace Notifier */


#endif /* NOTIFIER_BLANKNOTIFIER_H */

