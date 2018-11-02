/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataWriter.h
 * Author: user
 *
 * Created on 31 October 2018, 8:11 AM
 */

#ifndef FILE_DATAWRITER_H
#define FILE_DATAWRITER_H

#include "File/CsvDataWriter.h"
#include "File/JsonDataWriter.h"

namespace File {
    
    template <typename T>
    class DataWriter {
        DataWriter() = delete;
        DataWriter(const DataWriter&) = delete;
        DataWriter& operator=(const DataWriter&) = delete;
    public:
        static void write(const T& data, 
                          const std::string& filename, 
                          const std::string& filetype);
        
    }; /* class DataWriter */
    
    template <typename T>
    void
    DataWriter<T>::write(const T& data, 
                      const std::string& filename, 
                      const std::string& filetype) {
        if (filetype == "csv") {
            return CsvDataWriter<T>::write(data, filename);
        } else if (filetype == "json") {
            return JsonDataWriter<T>::write(data, filename);
        } else {
            throw std::runtime_error("Filetype not yet supported");
        }
    } 
    
} /* namespace File */

#endif /* FILE_DATAWRITER_H */

