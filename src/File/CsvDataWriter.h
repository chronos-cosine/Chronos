/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File/CsvDataWriter.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 31 October 2018, 10:52 PM
 */

#ifndef FILE_CSVDATAWRITER_H
#define FILE_CSVDATAWRITER_H

#include <boost/property_tree/ptree.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <string>

namespace fs = std::experimental::filesystem;

namespace File {
    
    template <typename T>
    class CsvDataWriter {
        CsvDataWriter() = delete;
        CsvDataWriter(const CsvDataWriter&) = delete;
        CsvDataWriter& operator=(const CsvDataWriter&) = delete;
    public:
        static void write(const T& data, 
                          const fs::path& destination, 
                          const char separator = '|') ;
        
    }; /* class CsvDataWriter */
    
    template <typename T>
    void 
    CsvDataWriter<T>::write(const T& data, 
                            const fs::path& destination, 
                            const char separator) {
        std::ofstream file(destination);
        
        if (!file.is_open()) {
            throw std::runtime_error("The file could not be opened");
        }
        file << "sep=" << separator << std::endl;

        bool first; 
        for (const auto& item: data) {
            boost::property_tree::ptree root;
            root << data;

            first = true;
            for (const auto& property: root) {
                if (first) {
                    first = false;
                } else {
                    file << separator;
                }

                file << property.second.get_value<std::string>();
            }

            file << std::endl;
        }
    } 
    
} /* namespace File */

#endif /* FILE_CSVDATAWRITER_H */

