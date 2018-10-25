/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Helpers.h
 * Author: user
 *
 * Created on 12 October 2018, 2:52 PM
 */

#ifndef CORE_HELPERS_H
#define CORE_HELPERS_H

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

namespace Core {
    namespace Helpers {
        template <typename KEY, typename VALUE>
        static std::set<VALUE> get_value_set(const std::map<KEY, VALUE>& map) {
            std::set<VALUE> values;
            for (const auto& pair: map) {
                values.insert(pair.second);
            }

            return values;
        }
        
        template <typename KEY, typename VALUE>
        static std::set<KEY> get_key_set(const std::map<KEY, VALUE>& map) {
            std::set<KEY> values;
            for (const auto& pair: map) {
                values.insert(pair.first);
            }

            return values;
        }
        
        template <typename KEY, typename VALUE>
        static std::ostream& print_map(std::ostream& lhs, const std::map<KEY, VALUE>& rhs) {
            lhs << "\n[\n";
            bool first = true;
            for (auto& pair: rhs) {
                if (first) { 
                    first = false;
                }
                else {
                    lhs << ",\n";
                }
                lhs << "\t{\"Key\": \"" << pair.first << "\", \"Value\": \"" << pair.second << "\"}";
            }
            lhs << "\n]" << std::endl;
        
            return lhs;
        }
        
    } /* namespace Helpers */
} /* namespace Core */

#endif /* CORE_HELPERS_H */

