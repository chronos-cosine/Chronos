/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternFileReader.h
 * Author: user
 *
 * Created on 04 October 2018, 9:48 AM
 */

#ifndef SORTER_PATTERNCSVFILEREADER_H
#define SORTER_PATTERNCSVFILEREADER_H

#include "Core/CsvFileReader.h"
#include "Sorter/Pattern.h"

#include <map>

namespace Sorter {
    
    class PatternCsvFileReader {
    public:
        PatternCsvFileReader(const PatternCsvFileReader&) = delete;
        PatternCsvFileReader& operator=(const PatternCsvFileReader&) = delete;
    public: 
        PatternCsvFileReader();
        virtual ~PatternCsvFileReader();
        
        std::map<unsigned long long, Pattern*> read(const char* filename) const;
    private:
        Core::CsvFileReader __csv_file_reader;
        
    };
    
} /* namespace Sorter */

#endif /* SORTER_PATTERNCSVFILEREADER_H */

