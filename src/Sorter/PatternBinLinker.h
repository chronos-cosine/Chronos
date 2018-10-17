/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternBinLinker.h
 * Author: user
 *
 * Created on 11 October 2018, 12:08 PM
 */

#ifndef SORTER_PATTERNBINLINKER_H
#define SORTER_PATTERNBINLINKER_H

#include "Sorter/Pattern.h"
#include "Sorter/Bin.h"

#include <map>
#include <memory>
#include <mutex>

namespace Sorter {

    class PatternBinLinker {
    public:
        PatternBinLinker(const PatternBinLinker&) = delete;
        PatternBinLinker& operator=(const PatternBinLinker&) = delete;
    public:
        PatternBinLinker();
        virtual ~PatternBinLinker();
        
        void link(const std::map<unsigned long long, std::shared_ptr<Pattern>>& patterns, 
                  const std::map<unsigned long long, std::shared_ptr<Bin>>& bins);
    private:
        std::mutex __mutex;
    };

} /* namespace Sorter */
    
#endif /* SORTER_PATTERNBINLINKER_H */

