/* 
 * File:   Input.hpp
 * Author: user
 *
 * Created on 01 October 2018, 7:16 AM
 */

#ifndef INPUT_HPP
#define INPUT_HPP

namespace WebHook 
{

class Input {
public:
    Input(const unsigned long long& id, const std::string& data);
    Input(const Input& orig);
    virtual ~Input();
    
    const unsigned long long& get_id() const;
    const std::string& get_data() const;
    
private:
    unsigned long long __id;
    std::string __data;
};

#endif /* INPUT_HPP */

