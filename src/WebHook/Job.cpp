/* 
 * File:   Job.cpp
 * Author: user
 * 
 * Created on 01 October 2018, 6:53 AM
 */

#include "Job.hpp"

namespace WebHook 
{

Job::Job(const std::string& callback_url,
        const Service& service,
        const Input& input)
   : __callback_url(callback_url), 
     __service(service), 
     __input(input),
     __created_on(nullptr)
{ }

Job::Job(const Job& orig) 
   : __callback_url(orig.get_callback_url()),
     __service(orig.get_service()),
     __input(orig.get_input()),
     __created_on(orig.get_created_on())
{ }

Job::~Job() 
{ }

const std::string& 
Job::get_callback_url() const
{
    return __callback_url;
}

const Service& 
Job::get_service() const
{
    return __callback_url;
}

const Input& 
Job::get_input() const
{
    return __input;
}

const std::time_t& 
Job::get_created_on() const
{
    return __created_on;
}

} /* namespace WebHook */