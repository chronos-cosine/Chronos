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

#ifndef SORTER_PATTERNFILEREADER_H
#define SORTER_PATTERNFILEREADER_H

#include "Core/CsvFileReader.h"
#include "Sorter/Pattern.h"

#include <map>

namespace Sorter {
    class PatternFileReader {
    public:
        PatternFileReader(const PatternFileReader&) = delete;
        PatternFileReader& operator=(const PatternFileReader&) = delete;
    public: 
        PatternFileReader();
        virtual ~PatternFileReader();
        
        std::map<unsigned long long, Pattern*> read(const char* filename) const;
    private:
        Core::CsvFileReader __csv_file_reader;
        
    }; /* class PatternFileReader */ 
    
} /* namespace Sorter */

#endif /* SORTER_PATTERNFILEREADER_H */

