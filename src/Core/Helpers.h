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

namespace Core {
    namespace Helpers {
        template <typename KEY, typename VALUE>
        static std::set<VALUE> get_value_set(const std::map<KEY, VALUE>& map) {
            std::set<VALUE> values;
            for (auto& pair: map) {
                values.insert(pair.second);
            }

            return values;
        }
        
    } /* namespace Helpers */
} /* namespace Core */

#endif /* CORE_HELPERS_H */

