/* 
 * File:   Job.hpp
 * Author: user
 *
 * Created on 01 October 2018, 6:53 AM
 */

#ifndef JOB_HPP
#define JOB_HPP

#include <ctime>
#include <string>

#include "Input.hpp"
#include "Service.hpp"


namespace WebHook 
{

class Job {
public:
    Job(const std::string& callback_url,
        const Service& service,
        const Input& input);
    Job(const Job& orig);
    virtual ~Job();
    
    const std::string& get_callback_url() const;
    const Service& get_service() const;
    const Input& get_input() const;
    const std::time_t& get_created_on() const; 
    
private:
    std::string __callback_url;
    Service __service;
    Input __input;
    std::time_t __created_on; 
};
 
} /* namespace WebHook */

#endif /* JOB_HPP */

