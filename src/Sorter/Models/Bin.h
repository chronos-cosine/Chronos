/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bin.h
 * Author: user
 *
 * Created on 15 November 2018, 1:20 PM
 */

#ifndef SORTER_MODELS_BIN_H
#define SORTER_MODELS_BIN_H

#include <boost/optional.hpp>
#include <string>

namespace Sorter {
    namespace Models {
        
        struct Bin {
            unsigned long long id;
            std::string name;
            boost::optional<unsigned long long> parent_id;
            
            bool is_root() const noexcept;
            bool operator==(const Bin& rhs) const noexcept;
            bool operator!=(const Bin& rhs) const noexcept;
            bool operator<(const Bin& rhs) const noexcept;
            Bin& operator=(const Bin& rhs);
            Bin& operator=(const Bin&& rhs);
        };
        
    } /* namespace Models */
} /* namespace Sorter */

#endif /* SORTER_MODELS_BIN_H */

