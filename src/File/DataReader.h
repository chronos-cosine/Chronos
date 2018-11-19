/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File/DataReader.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 29 October 2018, 10:52 PM
 */

#ifndef FILE_DATAREADER_H
#define FILE_DATAREADER_H

#include "File/CsvDataReader.h"
#include "File/FileType.h"
#include "File/JsonDataReader.h"

#include <exception>
#include <experimental/filesystem>
#include <string>
#include <vector>

namespace fs = std::experimental::filesystem;

namespace File {
    
    template <typename T>
    class DataReader {
        DataReader() = delete;
        DataReader(const DataReader&) = delete;
        DataReader& operator=(const DataReader&) = delete;
    public:
        static std::unique_ptr<std::vector<T>> 
        read(const fs::path& filename, const FileType& filetype);
        
    }; /* class DataReader */
        
    template <typename T>
    std::unique_ptr<std::vector<T>>
    DataReader<T>::read(const fs::path& filename, 
                        const FileType& filetype) {
        switch (filetype) {
            case FileType::CSV:
                return CsvDataReader::read<T>(filename);
            default:
                throw std::runtime_error("DataReader<T>::read() filetype not yet supported");
        }
    }
    
} /* namespace File */

#endif /* FILE_DATAREADER_H */

