/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResultFileWriter.cpp
 * Author: user
 * 
 * Created on 10 October 2018, 11:00 AM
 */

#include "ResultFileWriter.h"

#include <iostream>
#include <fstream>

namespace Sorter {

    ResultFileWriter::ResultFileWriter() { }

    ResultFileWriter::~ResultFileWriter() { }
    
    void 
    ResultFileWriter::write(const Result& result, const char* output_filename) {
        std::ofstream file(output_filename);
        if (file.is_open()) {
            file << result;
            file.close();
        }
    }

} /* namespace Sorter */
