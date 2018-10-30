/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JsonDataReader.h
 * Author: user
 *
 * Created on 30 October 2018, 2:41 PM
 */

#ifndef FILE_JSONDATAREADER_H
#define FILE_JSONDATAREADER_H

#include <string>
#include <vector>

namespace File {
    
    class JsonDataReader {
        JsonDataReader() = delete;
        JsonDataReader(const JsonDataReader&) = delete;
        JsonDataReader& operator=(const JsonDataReader&) = delete;
    public:        
        template <typename T> 
        static T read(const std::string& filename);
        
        template <typename T> 
        static std::vector<T> read_array(const std::string& filename);
        
    }; /* class JsonDataReader */

} /* namespace File */

#endif /* FILE_JSONDATAREADER_H */

