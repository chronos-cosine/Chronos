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

#include "Bin.h"

#include <map>

namespace Sorter {
    
    class BinFileReader {
    public: 
        //constructors
        BinFileReader(); 
        virtual ~BinFileReader();
        
        //member functions
        virtual std::set<Bin*> read(const char* path);
    private:
        char get_separator(const std::string& line);
        Bin* get_bin(const std::string& line, 
                     const char& separator,
                     const std::map<unsigned long long, Bin*> bins);

    };

} /* namespace Sorter */

#endif /* SORTER_BINFILEREADER_H */

