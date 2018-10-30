/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JsonDataReader.cpp
 * Author: user
 * 
 * Created on 30 October 2018, 2:41 PM
 */

#include "JsonDataReader.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace File {
    
    template <typename T>
    T 
    JsonDataReader::read(const std::string& filename) {
        std::ifstream file(filename);
        std::stringstream buffer; 
        boost::property_tree::ptree ptree;

        buffer << file.rdbuf();
        boost::property_tree::read_json(buffer, ptree);
        T object;
        object << ptree;

        return object;
    } /* T read(const std::string& filename) */

    template <typename T>
    std::vector<T> 
    JsonDataReader::read_array(const std::string& filename) {
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
    } /* std::vector<T> read_array(const std::string& filename) */
    
} /* namespace File */


