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

#include <mutex>
#include "Notifier/INotifier.h"

namespace Notifier {
    
    class CoutNotifier : public INotifier {
    private:
        std::mutex __mutex;
    public:
        virtual ~CoutNotifier();
        CoutNotifier();
        
        virtual void notify(const char* message);
    };

} /* namespace Notifier */

#endif /* NOTIFIER_COUTNOTIFIER_H */

