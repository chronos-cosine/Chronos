/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/BinCsvFileReader.h"

/* 
 * File:   BinFileReader.cpp
 * Author: user
 * 
 * Created on 04 October 2018, 2:48 PM
 */

#include "Sorter/Bin.h"
#include "Exceptions/Exception.h"
#include "File/CsvFileReader.h"

#include <exception>
#include <map>
#include <memory>
#include <vector>
#include <string>

namespace Sorter {
    
    BinCsvFileReader::BinCsvFileReader(const std::shared_ptr<Notifier::INotifier>& notifier)
            : __csv_file_reader(notifier), __notifier(notifier) { 
    
    }
    
    BinCsvFileReader::~BinCsvFileReader() { }
    
    std::map<unsigned long long, std::shared_ptr<Bin>>
    BinCsvFileReader::read(const std::string& filename) const { 
        std::map<unsigned long long, std::shared_ptr<Bin>> bins;
        std::vector<std::vector<std::string>> data(__csv_file_reader.read(filename));
        
        for (const std::vector<std::string>& row: data) {
            if (row.size() != 3) {
                thrower ("Bin document not in the correct format.");
            }
            
            unsigned long long id = std::stoull(row[0]);
            if (bins.find(id) == bins.end()) {
                bins[id] = std::shared_ptr<Bin>(new Bin(id, row[1], std::stoull(row[2])));
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