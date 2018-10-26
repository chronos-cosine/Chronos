/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvDataWriter.h
 * Author: user
 *
 * Created on 26 October 2018, 6:59 AM
 */

#ifndef FILE_CSVDATAWRITER_H
#define FILE_CSVDATAWRITER_H

#include "File/DataWriter.h"

#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <mutex>
#include <string>

namespace File {
    
    template <typename T>
    class CsvDataWriter : public DataWriter<T> {
    private:
        std::string __destination;
        std::ofstream __ofstream;
        std::mutex __mutex;
        char __separator;
    public:
        CsvDataWriter(const CsvDataWriter&) = delete;
        CsvDataWriter& operator=(const CsvDataWriter&) = delete;
        virtual ~CsvDataWriter();
        CsvDataWriter(const std::string& destination, char separator);
        
        virtual void write(const T& data); 
    };
    
    template <typename T>
    CsvDataWriter::~CsvDataWriter() {
        __ofstream.close();
    }
    
    template <typename T>
    CsvDataWriter::CsvDataWriter(const std::string& destination, char separator)
        : __destination(destination), 
          __ofstream(destination), 
          __separator(separator) {
    }
    
    template <typename T>
    void 
    CsvDataWriter::write(const T& data) {
        std::lock_guard<std::mutex> lock(__mutex);
        bool first;
        
        __ofstream << "sep=" << __separator << std::endl;
        
        for (const auto& item: data) {
            boost::property_tree::ptree root;
            root << data;

            first = true;
            for (const auto& property: root) {
                if (first) {
                    first = false;
                } else {
                    __ofstream << __separator;
                }
                
                __ofstream << property.second;
            }
            
            __ofstream << std::endl;
        }
    }
}

    

#endif /* FILE_CSVDATAWRITER_H */

