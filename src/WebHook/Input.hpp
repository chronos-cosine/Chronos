/* 
 * File:   Input.hpp
 * Author: user
 *
 * Created on 01 October 2018, 7:16 AM
 */

#ifndef WEBHOOK_INPUT_HPP
#define WEBHOOK_INPUT_HPP

namespace WebHook 
{

class Input {
public:
    Input(const unsigned long long& id, const std::string& data);
    Input(const Input& orig);
    virtual ~Input();
    
    const unsigned long long& get_id() const;
    const std::string& get_data() const;
    
    friend std::ostream& operator<<(std::ostream& stream, Input& input)
    {
        return stream << "{"
                      << "\"id\":\""
                      << input.get_id()
                      << "\",\"data\":\""
                      << input.get_data() 
                      << "\"}" << std::endl;
    }
private:
    unsigned long long __id;
    std::string __data;
};

#endif /* WEBHOOK_INPUT_HPP */

