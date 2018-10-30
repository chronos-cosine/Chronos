/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvDataReader.h
 * Author: user
 *
 * Created on 30 October 2018, 2:33 PM
 */

#ifndef FILE_CSVDATAREADER_H
#define FILE_CSVDATAREADER_H

#include <exception>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

namespace File { 
    
    class CsvDataReader {
        CsvDataReader() = delete;
        CsvDataReader(const CsvDataReader&) = delete;
        CsvDataReader& operator=(const CsvDataReader&) = delete;
    public:
        template <typename T>
        static std::vector<T> read(const std::string& filename);
        static std::vector<std::vector<std::string>> read(const std::string& filename);
    private:
        static char get_separator(const std::string& line);
        static std::vector<std::string> split(const std::string& line, const char& separator);
        
    };  /* class CsvDataReader */
    
    char
    CsvDataReader::get_separator(const std::string& line) {
        if (line.find("sep=") == std::string::npos) {
            throw std::invalid_argument("The first line of a Csv file must begin with sep=");
        }
        return line[4];
    } /* char get_separator() */

    std::vector<std::string> 
    CsvDataReader::split(const std::string& line, const char& separator) {
        std::istringstream line_stream(line);
        std::string column;
        std::vector<std::string> row;

        while (std::getline(line_stream, column, separator)) {
            row.push_back(column);
        }

        return row;
    } /* std::vector<std::string> split() */
    
    std::vector<std::vector<std::string>> 
    CsvDataReader::read(const std::string& filename) {
        std::ifstream file(filename);
        std::vector<std::vector<std::string>> data;
        std::string line;

        std::getline(file, line);
        char separator = get_separator(line);

        while (getline(file, line)) {
            if (line.size() > 0) {
                data.push_back(std::move(split(line, separator)));
            }
        }

        return data;
    } /* std::vector<std::vector<std::string>> read() */

    template <typename T>
    std::vector<T> 
    CsvDataReader::read(const std::string& filename) {
        std::vector<T> object;
        std::vector<std::vector<std::string>> data(std::move(read(filename)));
        for (const std::vector<std::string>& row: data) {
            T item;
            item << row;
            object.push_back(std::move(item));
        }

        return object;
    } /* std::vector<T> read() */
    
} /* namespace File */


#endif /* FILE_CSVDATAREADER_H */

