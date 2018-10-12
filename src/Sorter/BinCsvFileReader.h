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

#ifndef SORTER_BINCSVFILEREADER_H
#define SORTER_BINCSVFILEREADER_H

#include "Sorter/Bin.h"
#include "Core/CsvFileReader.h"

#include <map>
#include <memory>

namespace Sorter {
    
    class BinCsvFileReader {
    public:
        BinCsvFileReader(const BinCsvFileReader&) = delete;
        BinCsvFileReader& operator=(const BinCsvFileReader&) = delete;
    public: 
        BinCsvFileReader();
        virtual ~BinCsvFileReader();
        
        std::map<unsigned long long, std::shared_ptr<Bin>> read(const char* filename) const;
    private:
        Core::CsvFileReader __csv_file_reader;
        
    }; /* class BinFileReader */

} /* namespace Sorter */

#endif /* SORTER_BINCSVFILEREADER_H */

