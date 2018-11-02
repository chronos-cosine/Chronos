/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataReader.h
 * Author: user
 *
 * Created on 29 October 2018, 7:37 AM
 */

#ifndef FILE_DATAREADER_H
#define FILE_DATAREADER_H

#include "File/CsvDataReader.h"
#include "File/JsonDataReader.h"

#include <exception>
#include <string>
#include <vector>

namespace File {
    
    class DataReader {
        DataReader() = delete;
        DataReader(const DataReader&) = delete;
        DataReader& operator=(const DataReader&) = delete;
    public:
        template <typename T>
        static std::vector<T> read(const std::string& filename, const std::string& filetype);
        
    }; /* class DataReader */
        
    template <typename T>
    std::vector<T> 
    DataReader::read(const std::string& filename, const std::string& filetype) {
        if (filetype == "csv") {
            return CsvDataReader::read<T>(filename);
        } else if (filetype == "json") {
            return JsonDataReader<T>::read_array(filename);
        } else {
            throw std::runtime_error("Filetype not yet supported");
        }
    } /* std::vector<T> read(const std::string&, const std::string&) */
    
} /* namespace File */

#endif /* FILE_DATAREADER_H */

