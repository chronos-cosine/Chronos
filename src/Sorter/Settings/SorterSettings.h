/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SorterSettings.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 8:16 PM
 */

#ifndef SORTER_SETTINGS_SORTERSETTINGS_H
#define SORTER_SETTINGS_SORTERSETTINGS_H

#include "Sorter/Settings/BinSettings.h"
#include "Sorter/Settings/LoggerSettings.h"
#include "Sorter/Settings/PatternSettings.h"
#include "Sorter/Settings/ResultSettings.h"
#include "Sorter/Settings/SpoolerSettings.h"

namespace Sorter {
    namespace Settings {
        
        struct SorterSettings {
            BinSettings bin_settings;
            LoggerSettings logger_settings;
            PatternSettings pattern_settings;
            ResultSettings result_settings;
            SpoolerSettings spooler_settings;
            unsigned short sorter_instances;
        }; /* struct SorterSettings */
    
    } /* namespace Settings */
} /* namespace Sorter */

#endif /* SORTER_SETTINGS_SORTERSETTINGS_H */

