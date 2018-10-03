/* 
 * File:   Bin.hpp
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef SORTER_BIN_HPP
#define SORTER_BIN_HPP

#include <string>

namespace Sorter 
{

class Bin 
{
public:
    Bin(const std::string& name, const unsigned long long& id); 
    Bin(const std::string& name, const unsigned long long& id, Bin* parent); 
    virtual ~Bin();
    
    const Bin* get_parent() const;
    Bin* get_parent();
    
    const std::string& get_name() const;
    
    const unsigned long long& get_id() const;
    unsigned long long get_id();
private:
    Bin* __parent;
    std::string __name;
    unsigned long long __id;
};

} /* namespace Sorter */

#endif /* SORTER_BIN_HPP */

