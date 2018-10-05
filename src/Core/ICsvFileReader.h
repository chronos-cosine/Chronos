/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvFileReader.h
 * Author: user
 *
 * Created on 05 October 2018, 8:55 AM
 */

#ifndef CORE_CSVFILEREADER_H
#define CORE_CSVFILEREADER_H

#define CORE_CSVFILEREADER_SEPARATOR_PATTERN "sep="

#include <iostream>
#include <fstream>
#include <set>
#include <string>

namespace Core {

    template <typename T>
    class ICsvFileReader {
    public:
        virtual bool read_line(const std::string& line, 
                               const char& separator,
                               T** return_object) = 0;
    public:
        virtual std::set<T*> read(const char* filename);
    private:
        bool get_separator(const std::string& line, char& separator);
        
    }; /* class ICsvFileReader */
     
    template <typename T>
    bool 
    ICsvFileReader<T>::get_separator(const std::string& line, char& separator)
    {
        if (line.length() != 5
            || line.find(CORE_CSVFILEREADER_SEPARATOR_PATTERN) == std::string::npos)
        {
            return false;
        }
        separator = line[4];
        return true;
    }

    template <typename T>
    std::set<T*> 
    ICsvFileReader<T>::read(const char* filename)
    { 
        std::set<T*> return_object;
        std::ifstream file(filename);
        if (file)
        {
            std::string line;
            
            getline(file, line);
            char separator;
            if (!get_separator(line, separator))
            {
                file.close();
                std::cerr << "ERROR: The first line of the Pattern file must specify the separator to use." 
                          << std::endl << CORE_CSVFILEREADER_SEPARATOR_PATTERN 
                          << "<SEPARATOR> where <SEPARATOR> is a character to separate with. Example of a first line:" 
                          << std::endl << CORE_CSVFILEREADER_SEPARATOR_PATTERN << std::endl << std::endl;
                exit(1);
            }
            
            unsigned long long position = 1;
            while (getline(file, line))
            {
                ++position;
                T* object = nullptr;
                if (!read_line(line, separator, &object))
                {
                    file.close();
                    std::cerr << "ERROR: Could not create objects from the line that was read." << std::endl
                              << "Line Number: " << position << std::endl
                              << "Line: " << line; 
                    exit(1);
                }
                
                return_object.insert(object);
            }
            file.close();
        }
        
        return return_object;
    }
    
} /* namespace Core */
#endif /* CORE_CSVFILEREADER_H */

