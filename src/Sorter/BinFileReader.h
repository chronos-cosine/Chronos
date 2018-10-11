/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinFileReader.h
 * Author: user
 *
 * Created on 04 October 2018, 2:48 PM
 */

#ifndef SORTER_BINFILEREADER_H
#define SORTER_BINFILEREADER_H

#include "Sorter/Bin.h"
#include "Core/CsvFileReader.h"

#include <map>

namespace Sorter {
    
    class BinFileReader {
    public:
        BinFileReader(const BinFileReader&) = delete;
        BinFileReader& operator=(const BinFileReader&) = delete;
    public: 
        BinFileReader();
        virtual ~BinFileReader();
        
        std::map<unsigned long long, Bin*> read(const char* filename) const;
    private:
        Core::CsvFileReader __csv_file_reader;
        
    }; /* class BinFileReader */

} /* namespace Sorter */

#endif /* SORTER_BINFILEREADER_H */

