/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StartupSettingsFileReader.h
 * Author: theunis
 *
 * Created on 19 October 2018, 9:33 PM
 */

#ifndef SORTER_STARTUPSETTINGSFILEREADER_H
#define SORTER_STARTUPSETTINGSFILEREADER_H

#include "Sorter/StartupSettings.h"
#include "Notifier/INotifier.h"

#include <memory>
#include <string>

namespace Sorter {

class StartupSettingsFileReader {
    public:
        virtual ~StartupSettingsFileReader();
        StartupSettingsFileReader();
        
        StartupSettings read(const std::string& filename);
private: 
    std::shared_ptr<Notifier::INotifier> get_notifier(const std::string& notifier_type,
            unsigned short log_file_reset_minutes);
    std::map<unsigned long long, std::shared_ptr<Pattern>> read_patterns_file(const std::string& patterns_file_type,
            const std::string& patterns_file_location,
            const std::shared_ptr<Notifier::INotifier>& notifier);
    std::map<unsigned long long, std::shared_ptr<Bin>> read_bins_file(const std::string& bins_file_type,
            const std::string& bins_file_location,
            const std::shared_ptr<Notifier::INotifier>& notifier);
};

} /* namespace Sorter */

#endif /* SORTER_STARTUPSETTINGSFILEREADER_H */

