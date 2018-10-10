/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResultFileWriter.h
 * Author: user
 *
 * Created on 10 October 2018, 11:00 AM
 */

#ifndef SORTER_RESULTFILEWRITER_H
#define SORTER_RESULTFILEWRITER_H

#include "Sorter/Result.h"

namespace Sorter {

    class ResultFileWriter {
    public:
        ResultFileWriter();
        virtual ~ResultFileWriter();
        
        void write(const Result& result, const char* output_filename);

    }; /* class ResultFileWriter */

} /* namespace Sorter */

#endif /* RESULTFILEWRITER_H */

