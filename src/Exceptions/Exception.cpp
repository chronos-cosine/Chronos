/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Exceptions/Exception.h"

/* 
 * File:   CsvFileReader.cpp
 * Author: user
 * 
 * Created on 09 October 2018, 10:54 AM
 */

#include <sstream>
#include <stdexcept>
#include <regex>

namespace Exceptions {
    
Exception::Exception(const std::string &arg, const char *file, int line)
        : std::runtime_error(arg) {
    std::stringstream value;
    value << file << "; line " << line;
    __location = value.str();
    value.str(std::string());

    value << arg << "\n@ Location:" << __location;
    __message = value.str();
    __bare_message = arg;    
} 

Exception::~Exception() throw() { }

const char* 
Exception::what() const throw() {
    return __message.c_str();
}

const std::string&
Exception::what_bare() const throw() {
    return __bare_message;
}

const std::string&
Exception::what_location() const throw() {
    return __location;
}

static std::string getErrorStack(const std::exception& e, unsigned int level = 0) {
    std::string message = "ERROR: " + std::string(e.what());
    std::regex r("\n");
    message = std::regex_replace(message, r, "\n" + std::string(level, ' '));
    std::string stack_message = std::string(level, ' ') + message + "\n";
    try
    {
        std::rethrow_if_nested(e);
    }
    catch ( const std::exception& e )
    {
        stack_message += getErrorStack (e, level + 1);
    }
    return stack_message;
}

} /* namespace Exceptions */