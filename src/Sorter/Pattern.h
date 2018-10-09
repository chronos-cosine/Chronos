/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pattern.h
 * Author: user
 *
 * Created on 04 October 2018, 9:17 AM
 */

#ifndef SORTER_PATTERN_H
#define SORTER_PATTERN_H

#include "PatternMatcher/IPattern.h"
#include "Sorter/Bin.h"

#include <functional>
#include <iostream>

namespace Sorter {

    class Pattern : public PatternMatcher::IPattern {
        struct hash {
            std::size_t operator()(const Pattern& pattern) const noexcept {
                return std::hash<unsigned long long>{}(pattern.__id);
            }
        };  /* struct Pattern::hash */
    public:
        //constructors
        Pattern(const unsigned long long& id, const char* value, const unsigned long long& bin_id);
        Pattern(const unsigned long long& id, const std::string& value, const unsigned long long& bin_id);
        Pattern(const Pattern& orig);
        virtual ~Pattern();

        //member functions
        const unsigned long long& get_id() const;
        const unsigned long long& get_bin_id() const;
        Bin* get_bin() const; 
        void set_bin(Bin* bin);

        //operators
        virtual bool operator==(const Pattern& rhs) const;
        virtual bool operator!=(const Pattern& rhs) const;
        virtual bool operator<(const Pattern& rhs) const;
        virtual bool operator>(const Pattern& rhs) const;

        //friend operators
        friend std::ostream& operator<<(std::ostream& lhs, const Pattern& rhs);
    private:
        unsigned long long __id;
        unsigned long long __bin_id;
        Bin* __bin;
    }; /* class Pattern */

} /* namespace Sorter */

#endif /* SORTER_PATTERN_H */

