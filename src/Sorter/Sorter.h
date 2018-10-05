/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.h
 * Author: user
 *
 * Created on 05 October 2018, 8:53 AM
 */

#ifndef SORTER_SORTER_H
#define SORTER_SORTER_H

#include "Sorter/PatternFileReader.h"
#include "Sorter/BinFileReader.h"
#include "Sorter/MemoryManagement.h"

namespace Sorter {

class Sorter {
public:
    Sorter();
    Sorter(const Sorter& orig);
    virtual ~Sorter();
private:
    PatternFileReader pattern_file_reader;
    BinFileReader bin_file_reader;
    MemoryManagement memory_management;
    std::set<Bin*> bins;
};

} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

