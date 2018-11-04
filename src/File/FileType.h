/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileType.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 5:12 PM
 */

#ifndef FILE_FILETYPE_H
#define FILE_FILETYPE_H

#include <exception>
#include <string>
#include <stdexcept>

namespace File {
    
    enum FileType {
        CSV = 1,
        JSON = 2
    }; /* enum FileType */
        
}/* namespace File */

#endif /* FILE_FILETYPE_H */

