/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinFileReader.cpp
 * Author: user
 * 
 * Created on 04 October 2018, 2:48 PM
 */

#include "Sorter/BinFileReader.h"
#include "Sorter/Bin.h" 

#include <map>
#include <vector>

namespace Sorter {
    
    BinFileReader::BinFileReader() { }
    
    BinFileReader::~BinFileReader() { }
    
    std::map<unsigned long long, Bin*>
    BinFileReader::read(const char* filename) const {
        std::map<unsigned long long, Bin*> bins;
        std::vector<std::vector<std::string>> data(__csv_file_reader.read(filename));
        
        for (const std::vector<std::string>& row: data) {
            if (row.size() != 3) {
                throw std::runtime_error("Bin document not in the correct format.");
            }
            
            unsigned long long id = std::stoull(row[0]);
            if (bins.find(id) == bins.end()) {
                bins[id] = new Bin(id, row[1], std::stoull(row[2]));
            }
        }
        
        for (auto& pair: bins) {
            if (bins.find(pair.second->get_parent_id()) != bins.end()) {
                pair.second->set_parent(bins[pair.second->get_parent_id()]);
            }
        }
        
        return bins;
    }

} /* namespace Sorter */