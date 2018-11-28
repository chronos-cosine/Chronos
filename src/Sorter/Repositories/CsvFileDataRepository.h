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
            CsvFileDataRepository(const fs::path bins_file,
                                  const fs::path patterns_file);
            CsvFileDataRepository(const fs::path bins_file,
                                  const fs::path patterns_file,
                                  const std::shared_ptr<Notifier::INotifier>& notifier);
            
            virtual std::shared_ptr<Sorter::Data::DataContext> create_data_context();
        private:
            void read_bins(const std::shared_ptr<Sorter::Data::DataContext>& dc);
            void read_patterns(const std::shared_ptr<Sorter::Data::DataContext>& dc);
            void notify(const std::string& message) const;
        private:
            fs::path __bins_file;
            fs::path __patterns_file;
            std::shared_ptr<Notifier::INotifier> __notifier;
            
        }; /* class IDataRepository */
                
    } /* namespace Repositories */
} /* namespace Sorter */

#endif /* SORTER_SERVICES_FILEDATAREPOSITORY_H */

