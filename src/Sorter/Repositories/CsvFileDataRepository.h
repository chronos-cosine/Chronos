/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileDataRepository.h
 * Author: user
 *
 * Created on 19 November 2018, 9:29 AM
 */

#ifndef SORTER_SERVICES_FILEDATAREPOSITORY_H
#define SORTER_SERVICES_FILEDATAREPOSITORY_H

#include "Notifier/INotifier.h"
#include "Sorter/Repositories/IDataRepository.h"

#include <experimental/filesystem>
#include <memory>
#include <string>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    namespace Repositories {
        
        class CsvFileDataRepository : public IDataRepository {
            CsvFileDataRepository(const CsvFileDataRepository&) = delete;
            CsvFileDataRepository& operator=(const CsvFileDataRepository&) = delete;
        public:
            virtual ~CsvFileDataRepository() = default;
            
            CsvFileDataRepository(const fs::path t_bins_file,
                                  const fs::path t_patterns_file,
                                  const std::shared_ptr<Notifier::INotifier>& t_notifier);
            CsvFileDataRepository(const fs::path t_bins_file,
                                  const fs::path t_patterns_file);
            
            virtual std::shared_ptr<Sorter::Data::DataContext> create_data_context();
        private:
            void read_bins(const std::shared_ptr<Sorter::Data::DataContext>& t_dc);
            void read_patterns(const std::shared_ptr<Sorter::Data::DataContext>& t_dc);
            void notify(const std::string& t_message);
        private:
            std::shared_ptr<Notifier::INotifier> m_notifier;
            fs::path m_bins_file;
            fs::path m_patterns_file;
            
        }; /* class CsvFileDataRepository */
                
    } /* namespace Repositories */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_FILEDATAREPOSITORY_H */

