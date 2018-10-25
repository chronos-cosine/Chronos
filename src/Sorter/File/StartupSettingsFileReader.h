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

namespace Sorter {

class StartupSettingsFileReader {
    public:
        virtual ~StartupSettingsFileReader();
        StartupSettingsFileReader();
        
        StartupSettings read(const std::string& filename) const;
};

} /* namespace Sorter */

#endif /* SORTER_STARTUPSETTINGSFILEREADER_H */

