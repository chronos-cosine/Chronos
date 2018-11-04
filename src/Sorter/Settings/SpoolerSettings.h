/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SpoolerSettings.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 4:57 PM
 */

#ifndef SORTER_SETTINGS_SPOOLERSETTINGS_H
#define SORTER_SETTINGS_SPOOLERSETTINGS_H

#include <string>
#include <vector>

namespace Sorter {
    namespace Settings {
        
        struct SpoolerSettings {
            std::string trigger_extension;
            std::string busy_extension;
            std::vector<std::string> directories;
        }; /* struct SpoolerSettings */
        
    } /* namespace Settings */
} /* namespace Sorter */

#endif /* SORTER_SETTINGS_SPOOLERSETTINGS_H */

