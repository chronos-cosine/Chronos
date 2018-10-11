/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvFileReader.h
 * Author: user
 *
 * Created on 05 October 2018, 8:55 AM
 */

#ifndef CORE_CSVFILEREADER_H
#define CORE_CSVFILEREADER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

namespace Core {

    class CsvFileReader {
    public:
        CsvFileReader(const CsvFileReader&) = delete;
        CsvFileReader& operator=(const CsvFileReader&) = delete;
    public:
        CsvFileReader();
        virtual ~CsvFileReader();
        virtual std::vector<std::vector<std::string>> read(const char* filename) const;
    private:
        char get_separator(const std::string& line)  const;
        std::vector<std::string> get_row(const std::string& line, 
                                         const char& separator) const;
        
    }; /* class CsvFileReader */
    
} /* namespace Core */

#endif /* CORE_CSVFILEREADER_H */
