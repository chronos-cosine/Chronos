/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "IPattern.h"

namespace PatternMatcher
{
    //constructors
    IPattern::IPattern(const char* value)
            : __value(value) { }

    IPattern::IPattern(const std::string& value)
            : __value(value) { }

    IPattern::IPattern(const IPattern& value)
            : __value(value.__value) { }

    IPattern::~IPattern() { }

    //member functions
    const std::string& 
    IPattern::get_value() const {
        return __value;
    }

    std::string::iterator 
    IPattern::begin() {
        return __value.begin();
    }

    std::string::const_iterator 
    IPattern::begin() const {
        return __value.begin();
    }

    std::string::iterator 
    IPattern::end() {
        return __value.end();
    }

    std::string::const_iterator 
    IPattern::end() const {
        return __value.end();
    }

    //operators
    IPattern& 
    IPattern::operator=(const IPattern& rhs) {
        std::lock_guard<std::mutex> lock(__mutex);
        __value = rhs.__value;
        return *this;
    }

    IPattern& 
    IPattern::operator=(const std::string& rhs) {
        std::lock_guard<std::mutex> lock(__mutex);
        __value = rhs;
        return *this;
    }

    IPattern& 
    IPattern::operator=(const char* rhs) {
        std::lock_guard<std::mutex> lock(__mutex);
        __value = rhs;
        return *this;
    }

    bool 
    IPattern::operator==(const IPattern& rhs) const {
        return __value == rhs.__value;
    }

    bool 
    IPattern::operator!=(const IPattern& rhs) const {
        return __value != rhs.__value;
    }

    bool 
    IPattern::operator<(const IPattern& rhs) const {
        return __value < rhs.__value;
    }

    bool 
    IPattern::operator>(const IPattern& rhs) const {
        return __value > rhs.__value;
    }

    //friend operators
    std::ostream& 
    operator<<(std::ostream& lhs, const IPattern& rhs) {
        lhs << rhs.__value;
        return lhs;
    }

} /* namespace PatternMatcher */