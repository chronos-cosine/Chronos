/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File/CsvDataReader.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 30 October 2018, 2:33 PM
 */

#ifndef FILE_CSVDATAREADER_H
#define FILE_CSVDATAREADER_H

#include <exception>
#include <experimental/filesystem>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>

namespace fs = std::experimental::filesystem;

namespace File { 
    
    class CsvDataReader {
        CsvDataReader() = delete;
        CsvDataReader(const CsvDataReader&) = delete;
        CsvDataReader& operator=(const CsvDataReader&) = delete;
    public:
        template <typename T>
        static std::unique_ptr<std::vector<T>>
        read(const fs::path& filename);
       
        static std::unique_ptr<std::vector<std::vector<std::string>>>
        read(const fs::path& filename);
    private:
        static char get_separator(const std::string& line);
        static std::unique_ptr<std::vector<std::string>> 
            split(const std::string& line, const char& separator);
        static void validate_filename(const fs::path& filename);
        
    };  /* class CsvDataReader */
    
    void 
    CsvDataReader::validate_filename(const fs::path& filename) {
        if (!fs::exists(filename)) {
            throw std::runtime_error(
                "CsvDataReader::validate_filename() file does not exist");
        }
    }
    
    char
    CsvDataReader::get_separator(const std::string& line) {
        if (line.find("sep=") == std::string::npos) {
            throw std::invalid_argument(
                "CsvDataReader::get_separator() The first line of a Csv file must begin with sep=");
        }
        return line[4];
    }

    std::unique_ptr<std::vector<std::string>>
    CsvDataReader::split(const std::string& line, const char& separator) {
        std::istringstream line_stream(line);
        std::string column;
        std::unique_ptr<std::vector<std::string>> row = 
            std::make_unique<std::vector<std::string>>();

        while (std::getline(line_stream, column, separator)) {
            row->push_back(column);
        }

        return row;
    }
    
    std::unique_ptr<std::vector<std::vector<std::string>>>
    CsvDataReader::read(const fs::path& filename) {
        validate_filename(filename);
        
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("CsvDataReader::read() The file could not be opened");
        }
        
        std::unique_ptr<std::vector<std::vector<std::string>>> data = 
            std::make_unique<std::vector<std::vector<std::string>>>();
        std::string line;

        std::getline(file, line);
        char separator = get_separator(line);

        while (getline(file, line)) {
            if (line.size() > 0) {
                data->push_back(std::move(*split(line, separator)));
            }
        }

        return data;
    }

    template <typename T>
    std::unique_ptr<std::vector<T>>
    CsvDataReader::read(const fs::path& filename) {
        std::unique_ptr<std::vector<T>> object = std::make_unique<std::vector<T>>();
        std::unique_ptr<std::vector<std::vector<std::string>>> data = read(filename);
        for (const std::vector<std::string>& row: *data) {
            T item;
            item << row;
            object->push_back(std::move(item));
        }

        return object;
    }
    
} /* namespace File */


#endif /* FILE_CSVDATAREADER_H */

