/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Input.hpp
 * Author: user
 *
 * Created on 25 September 2018, 2:52 PM
 */

#ifndef PATTERNMATCHER_INPUT_HPP
#define PATTERNMATCHER_INPUT_HPP

#include <string>

namespace PatternMatcher
{
    
class Input {
public:
    Input(const std::string& pattern);
    Input(const Input& orig);
    virtual ~Input(); 
    
    std::string::const_iterator begin();
    std::string::const_iterator end();
    const std::string& get_value() const;
    std::string& get_value();
    
    //Operators
    Input& operator=(const std::string& rhs);
    Input& operator=(const Input& rhs); 
    bool operator==(const Input& rhs);
    bool operator!=(const Input& rhs);
    bool operator<(const Input& rhs) const;
    
    friend std::ostream& operator<<(std::ostream& stream, Input& input)
    {
        stream << input.get_value();

        return stream;
    }
private:
    std::string __input;
};

} /* namespace PatternMatcher */
#endif /* PATTERNMATCHER_INPUT_HPP */

