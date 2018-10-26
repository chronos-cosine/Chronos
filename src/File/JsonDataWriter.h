/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataWriter.h
 * Author: user
 *
 * Created on 26 October 2018, 6:46 AM
 */

#ifndef FILE_JSONDATAWRITER_H
#define FILE_JSONDATAWRITER_H

#include "File/DataWriter.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <mutex>
#include <string>

namespace File {
    
    template <typename T>
    class JsonDataWriter : public DataWriter<T> {
    private:
        std::string __destination;
        std::ofstream __ofstream;
        std::mutex __mutex;
    public:
        JsonDataWriter(const JsonDataWriter<T>&) = delete;
        JsonDataWriter<T>& operator=(const JsonDataWriter<T>&) = delete;
        virtual ~JsonDataWriter();
        JsonDataWriter(const std::string& destination);
        
        virtual void write(const T& data);
    };
    
    template <typename T>
    JsonDataWriter<T>::~JsonDataWriter() {
        __ofstream.close();
    }
    
    template <typename T>
    JsonDataWriter<T>::JsonDataWriter(const std::string& destination)
        : __destination(destination), __ofstream(destination) {
    }

    template <typename T>
    void 
    JsonDataWriter<T>::write(const T& data) {
        std::lock_guard<std::mutex> lock(__mutex);
        
        boost::property_tree::ptree root;
        root << data;

        boost::property_tree::write_json(__ofstream, root);
    }
}


#endif /* FILE_JSONDATAWRITER_H */

