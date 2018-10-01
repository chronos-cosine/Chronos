/* 
 * File:   Service.cpp
 * Author: user
 * 
 * Created on 01 October 2018, 6:57 AM
 */

#include "Service.hpp"

namespace WebHook 
{

Service::Service(const std::string& type, 
                 const std::string& posting_url) 
    : __type(type), 
      __posting_url(posting_url), 
      __sleep_until(nullptr)
{ }

Service::Service(const Service& orig) 
    : __type(orig.get_type()), 
      __posting_url(orig.get_posting_url()), 
      __sleep_until(orig.get_sleep_until())
{ }

Service::~Service() 
{ }

const std::string& 
Service::get_type() const
{
    return __type;
}

const std::string& 
Service::get_posting_url() const
{
    return __posting_url;
}

const std::time_t& 
Service::get_sleep_until() const
{
    return __sleep_until;
}

void 
Service::set_sleep_until(const std::time_t& sleep_until)
{
    __sleep_until = sleep_until;
}

} /* namespace WebHook */