/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvDataWriter.h
 * Author: user
 *
 * Created on 31 October 2018, 7:40 AM
 */

#ifndef FILE_CSVDATAWRITER_H
#define FILE_CSVDATAWRITER_H

#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <string>

namespace File {
    
    class CsvDataWriter {
        CsvDataWriter() = delete;
        CsvDataWriter(const CsvDataWriter&) = delete;
        CsvDataWriter& operator=(const CsvDataWriter&) = delete;
    public:
        template <typename T>
        static void write(const T& data, const std::string& destination, const char separator) ;
        
    }; /* class CsvDataWriter */
    
    template <typename T>
    void 
    CsvDataWriter::write(const T& data, const std::string& destination, const char separator) {
        std::ofstream ofstream(destination);
        bool first;

        ofstream << "sep=" << separator << std::endl;

        for (const auto& item: data) {
            boost::property_tree::ptree root;
            root << data;

            first = true;
            for (const auto& property: root) {
                if (first) {
                    first = false;
                } else {
                    ofstream << separator;
                }

                ofstream << property.second.get_value<std::string>();
            }

            ofstream << std::endl;
        }
    } /* write(const T& data, const std::string& destination, const char separator = '|') */
    
} /* namespace File */

#endif /* FILE_CSVDATAWRITER_H */

