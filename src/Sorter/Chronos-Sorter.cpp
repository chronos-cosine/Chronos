/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Chronos-Sorter.cpp
 * Author: user
 *
 * Created on 04 October 2018, 7:08 AM
 */
 
#include "PatternMatcher/PatternMatchingMachine.h"
#include "File/DataReader.h"
#include "Sorter/Bin.h"

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <exception>
#include <sstream>

void completed(const void* sender, 
        const std::string& input ,
        const unsigned long long& total_matches) {
    std::cout << "COMPLETED!!\n"
              << "Sender: " << sender
              << "\nInput: " << &input
              << "\nMatches: " << total_matches << std::endl;
}
    
void match_found(const void* sender , 
            const std::string& input ,
            const unsigned long long& position ,
            const std::set<std::string>& patterns) { 
    std::cout << "MATCHES FOUND!!\n"
              << "Sender: " << sender
              << "\nInput: " << &input
              << "\nPosition: " << position << std::endl;
    for (auto& p : patterns) {
        std::cout << p << ", ";
    }
    std::cout << std::endl << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "\nStarting Chronos-Sorter..." << std::endl;
    std::vector<Sorter::Bin> bins;
    std::string filename("./bins.dat");
    
    auto data = File::CsvDataReader::read("./bins.dat");
    
    unsigned long long i = 1;
    for (auto& row: data) {
        ++i;
        if (row.size() != 3) {
            std::stringstream message;
            message << "Unable to parse file " << filename << std::endl
                    << "@ line number " << i;
            
            throw std::runtime_error(message.str());
        }
        
        Sorter::Bin bin;
        bin.id = std::stoull(row[0]);
        bin.name = row[1];
        if (row[2].size() > 0) {
            bin.parent_id = std::stoull(row[2]);
        } else {
            bin.parent_id = 0;
        }
        
        bins.push_back(std::move(bin));
    }
    
    std::cout << "\nExiting Chronos-Sorter..." << std::endl;
    return 0;
}