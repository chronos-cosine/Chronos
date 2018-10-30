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
#include <iostream>
#include <fstream>
#include <string>

namespace File {
    
    namespace JsonDataWriter {
        
        template <typename T>
        std::ostream& write(std::ostream& ostream, const T& data) {
            boost::property_tree::ptree temp;
            temp << data;
            
            boost::property_tree::write_json(ostream, temp);
            
            return ostream;
        } /* write(std::ostream& ostream, const T& data) */
        
        template <typename T>
        void write(const T& data, const std::string& destination) {
            std::ofstream ofstream(destination); 

            write(ofstream, data);
        } /* write(const T& data, const std::string& destination) */ 
        
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

                    ofstream << property.second.get_value<std::string>();
                }

                ofstream << std::endl;
            }
        } /* write(const T& data, const std::string& destination, const char separator = '|') */
        
    } /* namespace CsvDataWriter */
    
} /* namespace File */ 


#endif /* FILE_DATAWRITER_H */

