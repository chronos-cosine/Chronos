/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternFileReader.cpp
 * Author: user
 * 
 * Created on 04 October 2018, 9:48 AM
 */
#include "Sorter/Pattern.h"
#include "Sorter/PatternCsvFileReader.h"

#include <map>

namespace Sorter {
    
    PatternCsvFileReader::PatternCsvFileReader() { }
    
    PatternCsvFileReader::~PatternCsvFileReader() { }
    
    std::map<unsigned long long, Pattern*> 
    PatternCsvFileReader::read(const char* filename) const {
        std::map<unsigned long long, Pattern*> patterns;
        std::vector<std::vector<std::string>> data(__csv_file_reader.read(filename));
        
        for (const std::vector<std::string>& row: data) {
            if (row.size() != 3) {
                throw std::runtime_error("Pattern document not in the correct format.");
            }
            
            unsigned long long id = std::stoull(row[0]);
            if (patterns.find(id) == patterns.end()) {
                patterns[id] = new Pattern(id, row[1], std::stoull(row[2]));
            }
        }
        
        return patterns;
    }
    
} /* namespace Sorter */
