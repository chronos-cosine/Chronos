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
#include "Processors/ProcessorBase.h"

#include <chrono>
#include <experimental/filesystem>
#include <memory>
#include <string>

namespace fs = std::experimental::filesystem;

namespace File {
   
    template <typename T = fs::path>
    class Spooler : public Processors::ProcessorBase {
         Spooler() = delete;
         Spooler(const Spooler&) = delete;
         Spooler& operator=(const Spooler&) = delete;
    public:
         virtual ~Spooler() = default;
         
         Spooler(const Spooler&& other);
         Spooler& operator=(const Spooler&& other);
         
         Spooler(const fs::path& directory,
                 const std::string& trigger,
                 const std::string& spooled_extension,
                 const std::chrono::seconds& sleep_time,
                 const std::shared_ptr<Collections::ICollection<T>>& collection);
    protected:
        virtual bool process();
    private:
         fs::path __directory;
         std::string __trigger;
         std::string __spooled_extension;
         std::shared_ptr<Collections::ICollection<T>> __collection;

    }; /* class Spooler */
    
    
    template <typename T>
    Spooler<T>::Spooler(const Spooler&& other) 
        : __directory(std::move(other.__directory)),
          __trigger(std::move(other.__trigger)),
          __spooled_extension(std::move(other.__spooled_extension)), 
          __collection(std::move(other.__collection)) {
    }
    
    template <typename T>
    Spooler<T>& 
    Spooler<T>::operator=(const Spooler&& other) {
        __directory = std::move(other.__directory);
        __trigger = std::move(other.__trigger);
        __spooled_extension = std::move(other.__spooled_extension);
        __collection = std::move(other.__collection);
    }
    
    template <typename T>
    Spooler<T>::Spooler(const fs::path& directory,
                     const std::string& trigger,
                     const std::string& spooled_extension,
                     const std::chrono::seconds& sleep_time,
                     const std::shared_ptr<Collections::ICollection<T>>& collection)
            : Processors::ProcessorBase(sleep_time), 
              __directory(directory), 
              __trigger(trigger), 
              __spooled_extension(spooled_extension), 
              __collection(collection) {
    }
    
    template <typename T>
    bool 
    Spooler<T>::process() {
        if (!fs::exists(__directory)) {
            throw std::runtime_error("Spooler::process() directory does not exist");
        }
        
        bool result = false;
        for (const auto& item: fs::directory_iterator(__directory)) {
            if (item.path().extension() == __trigger) {
                if (!result) {
                    result = true;
                }
                
                std::string new_filename = __directory.string() + 
                                            item.path().stem().c_str() +
                                            __spooled_extension;
                fs::path new_path(new_filename);
                
                try {
                    fs::rename(item, new_path);
                } catch (const fs::filesystem_error& e) {
                    return false;
                }
                
                __collection->push(new_path);
            }
        }
        
        return result;
    } 
    
} /* namespace File */

#endif /* FILE_SPOOLER_H */

