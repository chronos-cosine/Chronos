/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileDataRepository.cpp
 * Author: user
 * 
 * Created on 19 November 2018, 9:29 AM
 */

#include "CsvFileDataRepository.h"
#include "File/CsvDataReader.h"

namespace Sorter {
    namespace Repositories {
        
        CsvFileDataRepository::CsvFileDataRepository(const fs::path bins_file,
                              const fs::path patterns_file) 
                : __bins_file(bins_file), 
                  __patterns_file(patterns_file), 
                  __notifier(nullptr) {
        }
        
        CsvFileDataRepository::CsvFileDataRepository(const fs::path bins_file,
                              const fs::path patterns_file,
                              const std::shared_ptr<Notifier::INotifier>& notifier)
                : __bins_file(bins_file), 
                  __patterns_file(patterns_file), 
                  __notifier(notifier) {
            notify("CsvFileDataRepository::CsvFileDataRepository()");
        }
        
        void 
        CsvFileDataRepository::notify(const std::string& message) {
            if (nullptr != __notifier) {
                __notifier->notify(message);
            }
        }
        
        void 
        CsvFileDataRepository::read_bins(const std::shared_ptr<Sorter::Data::DataContext>& dc) {
            notify("CsvFileDataRepository::read_bins()");
            
            auto bins = File::CsvDataReader::read<Sorter::Models::Bin>(__bins_file);
            
            for (auto& bin: *bins) {
                dc->bins[bin.id] = std::make_shared<Sorter::Models::Bin>(std::move(bin));
            }
        }
        
        void 
        CsvFileDataRepository::read_patterns(const std::shared_ptr<Sorter::Data::DataContext>& dc) {
            notify("CsvFileDataRepository::read_patterns()");
            
            auto patterns = File::CsvDataReader::read<Sorter::Models::Pattern>(__patterns_file);
            
            for (auto& pattern: *patterns) {
                dc->patterns[pattern.id] = std::make_shared<Sorter::Models::Pattern>(std::move(pattern));
            }
        }
        
        std::shared_ptr<Sorter::Data::DataContext> 
        CsvFileDataRepository::create_data_context() {
            notify("CsvFileDataRepository::create_data_context()");
            
            auto dc = std::make_shared<Sorter::Data::DataContext>();
            
            read_bins(dc);
            read_patterns(dc);
            dc->link_bin_patterns();
            
            return dc;
        }
                
    } /* namespace Repositories */
} /* namespace Sorter */