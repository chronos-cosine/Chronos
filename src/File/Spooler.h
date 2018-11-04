/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File/Spooler.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 31 October 2018, 10:52 PM
 */

#ifndef FILE_SPOOLER_H
#define FILE_SPOOLER_H

#include "Collections/ICollection.h"
#include "Notifier/Notifiable.h"
#include "Notifier/INotifier.h"
#include "Processors/ProcessorBase.h"

#include <chrono>
#include <memory>
#include <string>

namespace File {
    
   class Spooler : public Processors::ProcessorBase {
        Spooler() = delete;
        Spooler(const Spooler&) = delete;
    public:
        virtual ~Spooler() = default;
        Spooler(const std::string& directory,
                const std::string& trigger,
                const std::string& busy_extension,
                const std::chrono::seconds& sleep_time,
                const std::shared_ptr<Collections::ICollection<std::string>>& collection);
   protected:
       virtual bool process();
    private:
        std::string __directory;
        std::string __trigger;
        std::string __busy_extension;
        std::shared_ptr<Collections::ICollection<std::string>> __collection;
        
    }; /* class Spooler */
    
} /* namespace File */



#endif /* FILE_SPOOLER_H */

