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

#include "Sorter/Repositories/CsvFileDataRepository.h"
#include "File/CsvDataReader.h"

namespace Sorter {
    namespace Repositories {
        
        CsvFileDataRepository::CsvFileDataRepository(
                        const fs::path t_bins_file,
                        const fs::path t_patterns_file) 
                : m_bins_file(t_bins_file), 
                  m_patterns_file(t_patterns_file), 
                  m_notifier(nullptr) {
        }
        
        CsvFileDataRepository::CsvFileDataRepository(const fs::path t_bins_file,
                              const fs::path t_patterns_file,
                              const std::shared_ptr<Notifier::INotifier>& t_notifier)
                : m_bins_file(t_bins_file), 
                  m_patterns_file(t_patterns_file), 
                  m_notifier(t_notifier) {
            notify("CsvFileDataRepository::CsvFileDataRepository()");
        }
        
        void 
        CsvFileDataRepository::read_bins(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context) {
            notify("CsvFileDataRepository::read_bins()");
            
            auto bins = File::CsvDataReader::read<Sorter::Models::Bin>(m_bins_file);
            
            for (auto& bin: *bins) {
                t_data_context->bins[bin.id] = std::make_shared<Sorter::Models::Bin>(bin);
            }
        }
        
        void 
        CsvFileDataRepository::read_patterns(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context) {
            notify("CsvFileDataRepository::read_patterns()");
            
            auto patterns = File::CsvDataReader::read<Sorter::Models::Pattern>(m_patterns_file);
            
            for (auto& pattern: *patterns) {
                t_data_context->patterns[pattern.id] = std::make_shared<Sorter::Models::Pattern>(pattern);
            }
        }
        
        std::shared_ptr<Sorter::Data::DataContext> 
        CsvFileDataRepository::create_data_context() {
            notify("CsvFileDataRepository::create_data_context()");
            
            std::shared_ptr<Sorter::Data::DataContext> data_context(std::make_shared<Sorter::Data::DataContext>(m_notifier));
            
            read_bins(data_context);
            read_patterns(data_context);
            data_context->link_bin_patterns();
            
            return data_context;
        }
        
        void 
        CsvFileDataRepository::notify(const std::string& t_message) {
            if (nullptr != m_notifier) {
                m_notifier->notify(t_message);
            }
        }
         
    } /* namespace Repositories */
} /* namespace Sorter */