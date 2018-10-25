/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArgumentReader.h
 * Author: user
 *
 * Created on 15 October 2018, 10:13 AM
 */

#ifndef CORE_ARGUMENTREADER_H
#define CORE_ARGUMENTREADER_H

#include <map>
#include <string>

namespace Core {
    
    namespace ArgumentReader {
        static std::map<std::string, std::string> read(int argc, char** argv) {
           std::map<std::string, std::string> values;
           values[std::string("-a")] = std::string(argv[0]);

           for (int i = 1; i < argc; i += 2) {
               if (i == argc - 1) {
                   values[std::string(argv[i])] = std::string();
               }
               else {
                   values[std::string(argv[i])] = std::string(argv[i + 1]);
               }
           }

           return values;
       }
    }
    
} /* namespace Core */

#endif /* CORE_ARGUMENTREADER_H */

