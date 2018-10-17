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

#ifndef EXCEPTIONS_EXCEPTION_H
#define EXCEPTIONS_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace Exceptions {
    
    class Exception : public std::runtime_error {
    private:
        std::string __message;
        std::string __bare_message;
        std::string __location;
    public: 
        Exception(const std::string &arg, const char *file, int line);
        virtual ~Exception() throw();
        virtual const char* what() const throw();
        const std::string& what_bare() const throw();
        const std::string& what_location() const throw();
    };
     
} /* namespace Exceptions */

#define thrower(arg) std::throw_with_nested(Exceptions::Exception(arg, __FILE__, __LINE__))

#endif /* EXCEPTIONS_EXCEPTION_H */

