/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File/JsonDataReader.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 30 October 2018, 2:41 PM
 */

#ifndef FILE_JSONDATAREADER_H
#define FILE_JSONDATAREADER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

namespace fs = std::experimental::filesystem;

namespace File {
    
    template <typename T> 
    class JsonDataReader {
        JsonDataReader();
        JsonDataReader(const JsonDataReader&) = delete;
        JsonDataReader& operator=(const JsonDataReader&) = delete;
    public:
        static std::unique_ptr<T> read(const std::string& filename);
    private:
        static void validate_filename(const std::string& filename);
        
    }; /* class JsonDataReader */
    
    template <typename T>
    void 
    JsonDataReader<T>::validate_filename(const std::string& filename) {
        if (!fs::exists(filename)) {
            throw std::runtime_error("JsonDataReader::validate_filename() file does not exist");
        }
    }
    
    template <typename T>
    std::unique_ptr<T> 
    JsonDataReader<T>::read(const std::string& filename) {
        validate_filename(filename);
        
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("JsonDataReader<T>::read() The file could not be opened");
        }
        
        std::stringstream buffer; 
        boost::property_tree::ptree ptree;

        buffer << file.rdbuf();
        boost::property_tree::read_json(buffer, ptree);
        std::unique_ptr<T> object = std::make_unique<T>();
        *object << ptree;

        return object;
    }
    
} /* namespace File */

#endif /* FILE_JSONDATAREADER_H */

