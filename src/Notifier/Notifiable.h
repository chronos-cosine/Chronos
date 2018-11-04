/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier/Notifiable.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 02 November 2018, 4:26 PM
 */

#ifndef NOTIFIER_NOTIFIABLE_H
#define NOTIFIER_NOTIFIABLE_H

#include "Notifier/NotifierBase.h"

#include <string>
#include <sstream>
#include <memory>

namespace Notifier {
    
    class Notifiable {
        Notifiable(const Notifiable&) = delete;
        Notifiable& operator=(const Notifiable&) = delete;
    public:
        virtual ~Notifiable() = default;
        Notifiable();
        Notifiable(const std::shared_ptr<NotifierBase>& notifier);
    protected:
        std::shared_ptr<NotifierBase> notifier;
    protected:
        void notify(const std::string& message);
        void notify(std::stringstream& message);
        
    }; /* class Notifiable */
    
} /* namespace Notifier */



#endif /* NOTIFIER_NOTIFIABLE_H */
