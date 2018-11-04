/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternSettings.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 5:09 PM
 */

#ifndef SORTER_SETTINGS_PATTERNSETTINGS_H
#define SORTER_SETTINGS_PATTERNSETTINGS_H

#include "File/FileType.h"

#include <string>

namespace Sorter {
    namespace Settings {
        
        struct PatternSettings {
            std::string filename;
            File::FileType file_type;
        }; /* struct PatternSettings */
        
    } /* namespace Settings */
} /* namespace Sorter */

#endif /* SORTER_SETTINGS_PATTERNSETTINGS_H */

