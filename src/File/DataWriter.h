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
    
    class DataWriter {
        DataWriter() = delete;
        DataWriter(const DataWriter&) = delete;
        DataWriter& operator=(const DataWriter&) = delete;
    public:
        template <typename T>
        static void write(const T& data, 
                          const std::string& filename, 
                          const std::string& filetype);
        
    }; /* class DataWriter */
    
    template <typename T>
    void
    DataWriter::write(const T& data, 
                      const std::string& filename, 
                      const std::string& filetype) {
        if (filetype == "csv") {
            return CsvDataWriter::write<T>(data, filename);
        } else if (filetype == "json") {
            return JsonDataWriter::write<T>(data, filename);
        } else {
            throw std::runtime_error("Filetype not yet supported");
        }
    } /* void write(const T&, const std::string&, const std::string&) */
    
} /* namespace File */

#endif /* FILE_DATAWRITER_H */

