/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File/JsonDataWriter.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 31 October 2018, 10:52 PM
 */

#ifndef FILE_JSONDATAWRITER_H
#define FILE_JSONDATAWRITER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <experimental/filesystem>
#include <string>
#include <fstream>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace File {
    
    template <typename T>
    class JsonDataWriter {
        JsonDataWriter() = delete;
        JsonDataWriter(const JsonDataWriter&) = delete;
        JsonDataWriter& operator=(const JsonDataWriter&) = delete;
    public:
        static std::ostream& write(std::ostream& ostream, const T& data);
        
        static void write(const T& data, const fs::path& destination);

    }; /* class JsonDataWriter */
    
    template <typename T>
    std::ostream& 
    JsonDataWriter<T>::write(std::ostream& ostream, const T& data) {
        boost::property_tree::ptree temp;
        data >> temp;

        boost::property_tree::write_json(ostream, temp);

        return ostream;
    } 
        
    template <typename T>
    void 
    JsonDataWriter<T>::write(const T& data, const fs::path& destination) {
        std::ofstream file(destination);
        if (!file.is_open()) {
            throw std::runtime_error("JsonDataWriter::write() The file could not be opened");
        }
        
        write(file, data);
    } 
    
} /* namespace File */

#endif /* FILE_JSONDATAWRITER_H */

