/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "File/CsvFileReader.h"

/* 
 * File:   CsvFileReader.cpp
 * Author: user
 * 
 * Created on 09 October 2018, 10:54 AM
 */

#include "Exceptions/Exception.h"

#include <sstream>
#include <string>

namespace File {

    CsvFileReader::~CsvFileReader() { }
    
    CsvFileReader::CsvFileReader(const std::shared_ptr<Notifier::INotifier>& notifier)
            : __notifier(notifier) { }
    
    char 
    CsvFileReader::get_separator(const std::string& line) const {
        if (line.find("sep=") == std::string::npos) {
            thrower ("The first line of a CSV file must begin with sep=");
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
            thrower ("Could not open csv file"); 
        }
        
        return data;
    }
    
} /* namespace core */ 
