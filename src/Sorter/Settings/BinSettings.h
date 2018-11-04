/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinSettings.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 5:19 PM
 */

#ifndef SORTER_SETTINGS_BINSETTINGS_H
#define SORTER_SETTINGS_BINSETTINGS_H

#include "File/FileType.h"

#include <string>

namespace Sorter {
    namespace Settings {
        
        struct BinSettings {
            std::string filename;
            File::FileType file_type;
        }; /* struct BinSettings */
        
    } /* namespace Settings */
} /* namespace Sorter */

#endif /* SORTER_SETTINGS_BINSETTINGS_H */

