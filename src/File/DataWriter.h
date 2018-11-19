/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File/DataWriter.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 31 October 2018, 10:52 PM
 */

#ifndef FILE_DATAWRITER_H
#define FILE_DATAWRITER_H

#include "File/CsvDataWriter.h"
#include "File/FileType.h"
#include "File/JsonDataWriter.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace File {
    
    template <typename T>
    class DataWriter {
        DataWriter() = delete;
        DataWriter(const DataWriter&) = delete;
        DataWriter& operator=(const DataWriter&) = delete;
    public:
        static void write(const T& data, 
                          const fs::path& filename, 
                          const FileType& filetype);
        
    }; /* class DataWriter */
    
    template <typename T>
    void
    DataWriter<T>::write(const T& data, 
                      const fs::path& filename, 
                      const FileType& filetype) {
        switch (filetype) {
            case FileType::CSV:
                CsvDataWriter<T>::write(data, filename);
                break;
            case FileType::JSON:
                JsonDataWriter<T>::write(data, filename);
                break;
            default:
                throw std::runtime_error("DataWriter<T>::write() filetype not yet supported");
        }
    } 
    
} /* namespace File */

#endif /* FILE_DATAWRITER_H */

