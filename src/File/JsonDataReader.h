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
        static T read(const std::string& filename);
        static std::shared_ptr<T> read_shared(const std::string& filename);
        
        static std::vector<T> read_array(const std::string& filename);
        static std::shared_ptr<std::vector<T>> read_array_shared(const std::string& filename);
    private:
        static void validate_filename(const std::string& filename);
        
    }; /* class JsonDataReader */
    
    template <typename T>
    void 
    JsonDataReader<T>::validate_filename(const std::string& filename) {
        if (!fs::exists(fs::path(filename))) {
            std::stringstream ss;
            ss << "JsonDataReader::read() filename \"" << filename << "\" supplied does not exist";
            
            throw std::runtime_error(ss.str().c_str());
        }
    }
    
    template <typename T>
    std::shared_ptr<T> 
    JsonDataReader<T>::read_shared(const std::string& filename) {
        validate_filename(filename);
        
        std::ifstream file(filename);
        std::stringstream buffer; 
        boost::property_tree::ptree ptree;

        buffer << file.rdbuf();
        boost::property_tree::read_json(buffer, ptree);
        std::shared_ptr<T> object = std::make_shared<T>();
        *object << ptree;

        return object;
    }
    
    template <typename T>
    std::shared_ptr<std::vector<T>> 
    JsonDataReader<T>::read_array_shared(const std::string& filename) {
        validate_filename(filename);
        
        std::ifstream file(filename);
        std::stringstream buffer; 
        boost::property_tree::ptree ptree;
        
        std::shared_ptr<std::vector<T>> object = std::make_shared<std::vector<T>>();

        buffer << file.rdbuf();
        boost::property_tree::read_json(buffer, ptree);

        for (auto& item: ptree.get_child("")) {
            T temp;
            temp << ptree;
            *object.push_back(std::move(temp));
        }

        return object;
    }
    
    template <typename T>
    T 
    JsonDataReader<T>::read(const std::string& filename) {
        validate_filename(filename);
        
        std::ifstream file(filename);
        std::stringstream buffer; 
        boost::property_tree::ptree ptree;

        buffer << file.rdbuf();
        boost::property_tree::read_json(buffer, ptree);
        T object;
        object << ptree;

        return object;
    } /* T read(const std::string&) */

    template <typename T>
    std::vector<T> 
    JsonDataReader<T>::read_array(const std::string& filename) {
        validate_filename(filename);
        
        std::ifstream file(filename);
        std::stringstream buffer; 
        boost::property_tree::ptree ptree;
        std::vector<T> object;

        buffer << file.rdbuf();
        boost::property_tree::read_json(buffer, ptree);

        for (auto& item: ptree.get_child("")) {
            T temp;
            temp << ptree;
            object.push_back(std::move(temp));
        }

        return object;
    } /* std::vector<T> read_array(const std::string&) */

} /* namespace File */

#endif /* FILE_JSONDATAREADER_H */

