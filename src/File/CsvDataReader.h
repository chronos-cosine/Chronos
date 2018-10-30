/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvDataReader.h
 * Author: user
 *
 * Created on 30 October 2018, 2:33 PM
 */

#ifndef FILE_CSVDATAREADER_H
#define FILE_CSVDATAREADER_H

#include <vector>
#include <string>

namespace File { 
    
    class CsvDataReader {
        CsvDataReader() = delete;
        CsvDataReader(const CsvDataReader&) = delete;
        CsvDataReader& operator=(const CsvDataReader&) = delete;
    public:
        template <typename T>
        static std::vector<T> read(const std::string& filename);
        static std::vector<std::vector<std::string>> read(const std::string& filename);
    private:
        char get_separator(const std::string& line);
        std::vector<std::string> split(const std::string& line, const char& separator);
        
    };  /* namespace CsvDataReader */
    
} /* namespace File */


#endif /* FILE_CSVDATAREADER_H */

