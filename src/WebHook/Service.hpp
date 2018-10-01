/* 
 * File:   Service.hpp
 * Author: user
 *
 * Created on 01 October 2018, 6:57 AM
 */

#ifndef WEBHOOK_SERVICE_HPP
#define WEBHOOK_SERVICE_HPP

#include <ctime>
#include <string>

namespace WebHook 
{

class Service {
public:
    Service(const std::string& type, const std::string& posting_url);
    Service(const Service& orig);
    virtual ~Service();
    
    const std::string& get_type() const;
    const std::string& get_posting_url() const;
    const std::time_t& get_sleep_until() const;
    void set_sleep_until(const std::time_t& sleep_until);
     
    friend std::ostream& operator<<(std::ostream& stream, Service& service)
    {
        return stream << "{"
                      << "\"type\":\""
                      << service.get_type()
                      << "\",\"posting_url\":\""
                      << service.get_posting_url()
                      << "\",\"sleep_until\":\""
                      << service.get_sleep_until()
                      << "\"}" << std::endl;
    }
private:
    std::string __type;
    std::string __posting_url;
    std::time_t __sleep_until;
};

} /* namespace WebHook */

#endif /* WEBHOOK_SERVICE_HPP */

