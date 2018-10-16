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

#include "Sorter/BooleanOperator.h"
#include "Sorter/Bin.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <set>

namespace Sorter {
    
    class Pattern {
    private:
        std::string __value;
        std::mutex __mutex;
        BooleanOperator __boolean_operator;
        unsigned long long __id;
        unsigned long long __bin_id;
        std::shared_ptr<Bin> __bin;
    public:
        //constructors
        Pattern(const unsigned long long& id, const char* value, 
                const unsigned long long& bin_id, const BooleanOperator& boolean_operator);
        Pattern(const unsigned long long& id, const std::string& value, 
                const unsigned long long& bin_id, const BooleanOperator& boolean_operator); 
        virtual ~Pattern();

        //member functions
        const unsigned long long& get_id() const;
        const unsigned long long& get_bin_id() const;
        const std::shared_ptr<Bin>& get_bin() const;
        const BooleanOperator& get_boolean_operator() const;
        void set_bin(const std::shared_ptr<Bin>& bin); 
        const std::string& get_value() const;
        
        std::string::const_iterator begin() const;
        std::string::const_iterator end() const;

        //operators 
        bool operator==(const Pattern& rhs) const;
        bool operator!=(const Pattern& rhs) const;
        bool operator<(const Pattern& rhs) const;
        bool operator>(const Pattern& rhs) const;

        //friend operators
        friend boost::property_tree::ptree& operator<<(boost::property_tree::ptree& lhs, const Pattern& rhs);
        friend std::ostream& operator<<(std::ostream& lhs, const Pattern& rhs);
        friend bool operator<(const std::shared_ptr<Pattern>& lhs, const std::shared_ptr<Pattern>& rhs);
        friend bool operator>(const std::shared_ptr<Pattern>& lhs, const std::shared_ptr<Pattern>& rhs);
        friend bool operator==(const std::shared_ptr<Pattern>& lhs, const std::shared_ptr<Pattern>& rhs);
        friend bool operator!=(const std::shared_ptr<Pattern>& lhs, const std::shared_ptr<Pattern>& rhs);
    public:
        Pattern() = delete;
        Pattern(Pattern&) = delete;
        Pattern(Pattern&&) = delete;
        Pattern& operator=(Pattern&) = delete;
        Pattern& operator=(Pattern&&) = delete;
    public:
        struct Hasher {
            std::size_t operator()(const Pattern& pattern) const noexcept {
                return std::hash<unsigned long long>{}(pattern.__id);
            }
        }; 
    }; /* class Pattern */

} /* namespace Sorter */

#endif /* SORTER_PATTERN_H */

