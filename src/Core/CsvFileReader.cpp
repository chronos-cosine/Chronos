/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvFileReader.cpp
 * Author: user
 * 
 * Created on 09 October 2018, 10:54 AM
 */

#include "CsvFileReader.h"

#include <exception>
#include <sstream>

namespace Core {

    CsvFileReader::CsvFileReader() { }
    
    CsvFileReader::~CsvFileReader() { }
        
    char 
    CsvFileReader::get_separator(const std::string& line) const {
        if (line.length() != 5
            || line.find("sep=") == std::string::npos) {
            throw std::runtime_error("The first line of a CSV file must begin with sep= and must be exactly 5 characters in length.");
        }
        return line[4];
    }
       
    std::vector<std::string> 
    CsvFileReader::get_row(const std::string& line, const char& separator) const {
        std::istringstream line_stream(line);
        std::string column;
        std::vector<std::string> row;
        
        while (getline(line_stream, column, separator)) {
            row.push_back(column);
        }
        
        return row;
    }

    std::vector<std::vector<std::string>>
    CsvFileReader::read(const char* filename) const { 
        std::vector<std::vector<std::string>> data;
        std::ifstream file(filename);
        
        if (file.is_open()) {
            std::string line; 
            getline(file, line);
            
            char separator = get_separator(line);
            while (getline(file, line)) {
                data.push_back(get_row(line, separator));
            }
        } else {
            throw std::runtime_error("Could not open csv file.");
        }
        
        return data;
    }
    
} /* namespace core */ 
