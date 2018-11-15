/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IProcessor.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 10:11 AM
 */

#ifndef PROCESSORS_IPROCESSOR_H
#define PROCESSORS_IPROCESSOR_H

namespace Processors {

    class IProcessor {
        IProcessor(const IProcessor&) = delete;
        IProcessor& operator=(const IProcessor&) = delete;
        IProcessor(const IProcessor&&) = delete;
        IProcessor& operator=(const IProcessor&&) = delete;
    public:
        virtual ~IProcessor() = default;
        IProcessor() = default;
        
        virtual bool start() = 0;
        virtual bool stop() noexcept = 0;
        virtual bool get_is_running() const noexcept = 0; 
        virtual bool get_is_executing() const noexcept = 0;
        virtual bool get_is_stopping() const noexcept = 0;
    protected:
        virtual bool process() = 0;
        
    }; /* class IProcessor */
    
} /* namespace Processors */

#endif /* PROCESSORS_IPROCESSOR_H */

