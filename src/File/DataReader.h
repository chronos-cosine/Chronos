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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <exception>
#include <fstream>
#include <string>
#include <vector>

namespace File {
    
    namespace JsonDataReader {
        
        template <typename T>
        T read(const std::string& filename) {
            std::ifstream file(filename);
            std::stringstream buffer; 
            boost::property_tree::ptree ptree;
            
            buffer << file.rdbuf();
            boost::property_tree::read_json(buffer, ptree);
            T object;
            object << ptree;
            
            return object;
        } /* read() */
        
    } /* namespace JsonDataReader */
    
    namespace CsvDataReader {
        
        namespace detail {
            char get_separator(const std::string& line) {
                if (line.find("sep=") == std::string::npos) {
                    throw std::invalid_argument("The first line of a Csv file must begin with sep=");
                }
                return line[4];
            }
            
            std::vector<std::string> 
            split(const std::string& line, const char& separator) {
                std::istringstream line_stream(line);
                std::string column;
                std::vector<std::string> row;

                while (std::getline(line_stream, column, separator)) {
                    row.push_back(column);
                }

                return row;
            }
        } /* namespace detail */
        
        std::vector<std::vector<std::string>> read(const std::string& filename) {
            std::ifstream file(filename);
            std::vector<std::vector<std::string>> data;
            std::string line;
            
            std::getline(file, line);
            char separator = detail::get_separator(line);

            while (getline(file, line)) {
                if (line.size() > 0) {
                    data.push_back(std::move(detail::split(line, separator)));
                }
            }

            return data;
        } /* read() */
        
    } /* namespace CsvFileReader */
    
} /* namespace File */


#endif /* FILE_DATAREADER_H */

