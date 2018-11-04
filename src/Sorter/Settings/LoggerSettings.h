/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LoggerSettings.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 5:03 PM
 */ 
#ifndef SORTER_SETTINGS_LOGGERSETTINGS_H
#define SORTER_SETTINGS_LOGGERSETTINGS_H

#include <chrono>
#include <string>
#include <vector>
#include <exception>

namespace Sorter {
    namespace Settings {
        
        enum LoggingType {
            FILE = 1,
            COUT = 2
        }; /* enum LoggingType */
        
        struct LoggerSettings {
            std::chrono::minutes cycle_time;
            std::string output_directory;
            LoggingType type;
        }; /* struct SpoolerSettings */
        
    } /* namespace Settings */
} /* namespace Sorter */


#endif /* SORTER_SETTINGS_LOGGERSETTINGS_H */

