/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Core/CsvFileReader.h"

/* 
 * File:   CsvFileReader.cpp
 * Author: user
 * 
 * Created on 09 October 2018, 10:54 AM
 */

#include "Core/Exception.h"

#include <exception>
#include <sstream>
#include <string>

namespace Core {

    CsvFileReader::CsvFileReader() { }
    
    CsvFileReader::~CsvFileReader() { }
        
    char 
    CsvFileReader::get_separator(const std::string& line) const {
        if (line.length() != 5
            || line.find("sep=") == std::string::npos) {
            thrower ("The first line of a CSV file must begin with sep= and must be exactly 5 characters in length.");
        }
        return line[4];
    }
       
    std::vector<std::string> 
    CsvFileReader::get_row(const std::string& line, const char& separator) const {
        try {
            std::istringstream line_stream(line);
            std::string column;
            std::vector<std::string> row;

            while (getline(line_stream, column, separator)) {
                row.push_back(column);
            }

            return row;
        } catch (std::exception& e) {
            thrower ("ERROR: Core::CsvFileReader::get_row\n: ");
        }
    }

    std::vector<std::vector<std::string>>
    CsvFileReader::read(const std::string& filename) const {
        std::vector<std::vector<std::string>> data;
        std::ifstream file(filename.c_str());
        
        if (file.is_open()) {
            std::string line; 
            getline(file, line);
            
            char separator = get_separator(line);
            while (getline(file, line)) {
                data.push_back(get_row(line, separator));
            }
        } else { 
            thrower ("\nERROR: Core::CsvFileReader::read\nCould not open csv file\n"); 
        }
        
        return data;
    }
    
} /* namespace core */ 
