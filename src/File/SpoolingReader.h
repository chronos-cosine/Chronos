/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SpoolingReader.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 10:04 PM
 */

#ifndef FILE_SPOOLINGREADER_H
#define FILE_SPOOLINGREADER_H

#include "Collections/ICollection.h"
#include "Processors/ProcessorBase.h"
#include "JsonDataReader.h"

#include <memory>
#include <string>

namespace File {
    template <typename T>
    class SpoolingReader : Processors::ProcessorBase {
        SpoolingReader(const SpoolingReader&) = delete;
    public:
        virtual ~SpoolingReader() = default;
        SpoolingReader(const std::shared_ptr<Collections::ICollection<std::string>>& filenames,
                       const std::shared_ptr<Collections::ICollection<T>>& items);
    protected:
        virtual bool process();
    private:
        std::shared_ptr<Collections::ICollection<std::string>> __filenames;
        std::shared_ptr<Collections::ICollection<T>> __output;
    }; /* class SpoolingReader */
    
    template <typename T>
    SpoolingReader::SpoolingReader(
            const std::shared_ptr<Collections::ICollection<std::string>>& filenames,
            const std::shared_ptr<Collections::ICollection<std::shared_ptr<T>>>& output) 
      : __filenames(filenames), __output(output) {
    }
    
    template <typename T>
    bool
    SpoolingReader::process() {
        __output.push(JsonDataReader<T>::read(__filenames->pop()));
        return true;
    }
    
} /* namespace File */


#endif /* FILE_SPOOLINGREADER_H */

