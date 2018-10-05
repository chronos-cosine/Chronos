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
#include "Core/ICsvFileReader.h" 

namespace Sorter {
    
    class BinFileReader : public Core::ICsvFileReader<Sorter::Bin> {
    public: 
        BinFileReader();
        virtual ~BinFileReader();
        virtual bool read_line(const std::string& line, 
                               const char& separator,
                               Sorter::Bin** bin);
        virtual std::set<Sorter::Bin*> read(const char* filename);
    private:
        std::set<unsigned long long> __added;
    }; /* class BinFileReader */

} /* namespace Sorter */

#endif /* SORTER_BINFILEREADER_H */

