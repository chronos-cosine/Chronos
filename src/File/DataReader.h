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
        
        template <typename T>
        std::vector<T> 
        read_array(const std::string& filename) {
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
        } /* std::vector<T> read_list(const std::string& filename) */
        
    } /* namespace JsonDataReader */
    
    namespace CsvDataReader {
        
        namespace detail {
            char get_separator(const std::string& line) {
                if (line.find("sep=") == std::string::npos) {
                    throw std::invalid_argument("The first line of a Csv file must begin with sep=");
                }
                return line[4];
            } /* char get_separator() */
            
            std::vector<std::string> 
            split(const std::string& line, const char& separator) {
                std::istringstream line_stream(line);
                std::string column;
                std::vector<std::string> row;

                while (std::getline(line_stream, column, separator)) {
                    row.push_back(column);
                }

                return row;
            } /* std::vector<std::string> split() */
            
        } /* namespace detail */
        
        std::vector<std::vector<std::string>> 
        read(const std::string& filename) {
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
        } /* std::vector<std::vector<std::string>> read() */
        
        template <typename T>
        std::vector<T> 
        read(const std::string& filename) {
            std::vector<T> object;
            std::vector<std::vector<std::string>> data(std::move(read(filename)));
            for (const std::vector<std::string>& row: data) {
                T item;
                item << row;
                object.push_back(std::move(item));
            }
            
            return object;
        } /* std::vector<T> read() */
        
    } /* namespace CsvFileReader */
    
    template <typename T>
    std::vector<T> 
    read_array(const std::string& filename, const std::string& filetype) {
        if (filetype == "csv") {
            return CsvDataReader::read<T>(filename);
        } else if (filetype == "json") {
            return JsonDataReader::read_array<T>(filename);
        } else {
            throw std::runtime_error("Filetype not yet supported");
        }
    }
    
} /* namespace File */


#endif /* FILE_DATAREADER_H */

