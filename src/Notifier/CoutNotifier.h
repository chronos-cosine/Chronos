/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Notifier/CoutNotifier.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 17 October 2018, 10:52 PM
 */

#ifndef NOTIFIER_COUTNOTIFIER_H
#define NOTIFIER_COUTNOTIFIER_H

#include "Notifier/INotifier.h"

#include <mutex>
#include <string>

namespace Notifier {
    
    class CoutNotifier : public INotifier {
        CoutNotifier(const CoutNotifier&) = delete;
        CoutNotifier& operator=(const CoutNotifier&) = delete;
    private:
        std::mutex __mutex;
    public:
        virtual ~CoutNotifier() = default;
        CoutNotifier() = default;
        
        virtual void notify(const std::string& message);
        virtual void notify(std::stringstream& message);
    };

} /* namespace Notifier */

#endif /* NOTIFIER_COUTNOTIFIER_H */

