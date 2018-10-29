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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <string>

namespace File {
    
    namespace JsonDataWriter {
        
        template <typename T>
        void write(const T& data, const std::string& destination) {
            std::ofstream ofstream(destination);
            boost::property_tree::ptree root;
            root << data;

            boost::property_tree::write_json(ofstream, root);
        } /* write() */ 
        
    } /* namespace JsonDataWriter */
    
    namespace CsvDataWriter {
        
        template <typename T>
        void write(const T& data, const std::string& destination, const char separator = '|') {
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

                    ofstream << property.second;
                }

                ofstream << std::endl;
            }
        } /* write() */
        
    } /* namespace CsvDataWriter */
    
} /* namespace File */ 


#endif /* FILE_DATAWRITER_H */

