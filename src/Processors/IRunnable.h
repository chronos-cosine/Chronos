/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IRunnable.h
 * Author: user
 *
 * Created on 18 December 2018, 1:52 PM
 */

#ifndef PROCESSORS_IRUNNABLE_H
#define PROCESSORS_IRUNNABLE_H

namespace Processors {

    class IRunnable {
    public:
        virtual bool start() = 0;
        virtual bool stop() = 0;
        virtual bool get_is_running() const noexcept = 0;
        virtual bool get_is_stopping() const noexcept = 0;
    }; /* class IRunnable */
    
} /* namespace Processors */

#endif /* IRUNNABLE_H */

