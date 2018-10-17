/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternFileReader.h
 * Author: user
 *
 * Created on 04 October 2018, 9:48 AM
 */

#ifndef SORTER_PATTERNCSVFILEREADER_H
#define SORTER_PATTERNCSVFILEREADER_H

#include "File/CsvFileReader.h"
#include "Sorter/Pattern.h"
#include "Notifier/INotifier.h"

#include <map>
#include <memory>
#include <string>

namespace Sorter {
    
    class PatternCsvFileReader {
    private:
        File::CsvFileReader __csv_file_reader;
        std::shared_ptr<Notifier::INotifier> __notifier;
    public: 
        PatternCsvFileReader(const std::shared_ptr<Notifier::INotifier>& notifier);
        virtual ~PatternCsvFileReader();
        
        std::map<unsigned long long, std::shared_ptr<Pattern>> read(const std::string& filename) const;
    public:
        PatternCsvFileReader(const PatternCsvFileReader&) = delete;
        PatternCsvFileReader& operator=(const PatternCsvFileReader&) = delete;
        
    };
    
} /* namespace Sorter */

#endif /* SORTER_PATTERNCSVFILEREADER_H */

