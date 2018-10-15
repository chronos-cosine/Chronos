/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.h
 * Author: user
 *
 * Created on 15 October 2018, 11:44 AM
 */

#ifndef CORE_EXCEPTION_H
#define CORE_EXCEPTION_H

#include <sstream>
#include <stdexcept>
#include <regex>

namespace Core {
    
    class Exception : public std::runtime_error {
    public: 
        Exception(const std::string &arg, const char *file, int line)
            : std::runtime_error(arg) {
                __location = std::string (file) + "; line " + std::to_string (line);
                std::ostringstream out;
                out << arg << "\n@ Location:" << __location;
                __message = out.str( );
                __bare_message = arg;    
            } 
        virtual ~Exception() throw() { }
        virtual const char* what() const throw() {
            return __message.c_str();
        }
        std::string what_bare() const throw() {
            return __bare_message;
        }
        std::string what_location() const throw() {
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
     private:
            std::string __message;
            std::string __bare_message;
            std::string __location;

    };
    
    #define thrower(arg) std::throw_with_nested(Exception(arg, __FILE__, __LINE__))

} /* namespace Core */


#endif /* CORE_EXCEPTION_H */

