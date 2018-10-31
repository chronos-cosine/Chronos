/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JsonDataWriter.h
 * Author: user
 *
 * Created on 31 October 2018, 7:15 AM
 */

#ifndef FILE_JSONDATAWRITER_H
#define FILE_JSONDATAWRITER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <fstream>
#include <iostream>

namespace File {
    
    class JsonDataWriter {
        JsonDataWriter() = delete;
        JsonDataWriter(const JsonDataWriter&) = delete;
        JsonDataWriter& operator=(const JsonDataWriter&) = delete;
    public:
        template <typename T>
        static std::ostream& write(std::ostream& ostream, const T& data);
        template <typename T>
        static void write(const T& data, const std::string& destination);

    }; /* class JsonDataWriter */
    
    template <typename T>
    std::ostream& 
    JsonDataWriter::write(std::ostream& ostream, const T& data) {
        boost::property_tree::ptree temp;
        temp << data;

        boost::property_tree::write_json(ostream, temp);

        return ostream;
    } /* write(std::ostream& ostream, const T& data) */
        
    template <typename T>
    void 
    JsonDataWriter::write(const T& data, const std::string& destination) {
        std::ofstream ofstream(destination); 

        write(ofstream, data);
    } /* write(const T& data, const std::string& destination) */ 
    
} /* namespace File */

#endif /* FILE_JSONDATAWRITER_H */

