/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier/Notifiable.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 02 November 2018, 4:26 PM
 */

#include "Notifier/Notifiable.h"

#include <string>
#include <sstream>
#include <memory>

namespace Notifier {
    Notifiable::Notifiable()
        : m_notifier(std::shared_ptr<Notifier::INotifier>(nullptr)) {
    }
    
    Notifiable::Notifiable(const std::shared_ptr<Notifier::INotifier>& t_notifier) 
        : m_notifier(t_notifier) {
    }
    
    
    std::shared_ptr<INotifier> 
    Notifiable::get_notifier() {
        return m_notifier;
    }
    
    void 
    Notifiable::notify(const std::string& message) {
        if (nullptr != m_notifier) {
            m_notifier->notify(message);
        }
    }
    
    void 
    Notifiable::notify(std::stringstream& message) {
        if (nullptr != m_notifier) {
            m_notifier->notify(message);
        }
    }
        
} /* namespace Notifier */