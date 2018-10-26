/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataWriter.h
 * Author: user
 *
 * Created on 26 October 2018, 7:19 AM
 */

#ifndef FILE_DATAWRITER_H
#define FILE_DATAWRITER_H

namespace File {
    
    template <typename T>
    class DataWriter {
    public:
        DataWriter& operator=(const DataWriter&) = delete;
        DataWriter(const DataWriter&) = delete;
        
        DataWriter() { }
        virtual ~DataWriter() { };
        virtual void write(const T& data) = 0; 
    };
        
}


#endif /* FILE_DATAWRITER_H */

