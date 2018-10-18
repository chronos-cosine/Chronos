/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NotifyBase.h
 * Author: user
 *
 * Created on 18 October 2018, 8:27 AM
 */

#ifndef NOTIFIER_NOTIFIABLE_H
#define NOTIFIER_NOTIFIABLE_H

#include "Notifier/INotifier.h"
#include <memory>

namespace Notifier {
    
    class Notifiable {
        std::shared_ptr<INotifier> __notifier;
    public:
        Notifiable(const std::shared_ptr<INotifier>& notifier);
        ~Notifiable();
    protected:
        void notify(const std::string& message);
    public:
        Notifiable(Notifiable&) = delete;
        Notifiable& operator=(Notifiable&) = delete;
        Notifiable(Notifiable&&) = delete;
        Notifiable& operator=(Notifiable&&) = delete;

    };

} /* namespace Notifier */

#endif /* NOTIFIER_NOTIFIABLE_H */

