/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Spooler.h
 * Author: user
 *
 * Created on 31 October 2018, 9:16 AM
 */

#ifndef FILE_SPOOLER_H
#define FILE_SPOOLER_H

#include "Processors/IProcessor.h"
#include "Collections/ICollection.h"

#include <memory>
#include <string>

namespace File {
    
   class Spooler : public Processors::IProcessor {
        Spooler() = delete;
        Spooler(const Spooler&) = delete;
    public:
        virtual ~Spooler();
        Spooler(const std::string& directory,
                const std::string& trigger,
                const std::shared_ptr<Collections::ICollection<std::string>>& collection);
   protected:
       virtual bool process();
    private:
        std::string __directory;
        std::string __trigger;
        std::shared_ptr<Collections::ICollection<std::string>> __collection;
        
    }; /* class Spooler */
    
} /* namespace File */



#endif /* FILE_SPOOLER_H */

