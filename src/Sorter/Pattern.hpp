/* 
 * File:   Pattern.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:47 AM
 */

#ifndef SORTER_PATTERN_HPP
#define SORTER_PATTERN_HPP

#include <string>

#include "../PatternMatcher/Pattern.hpp"

namespace Sorter 
{

class Pattern : public PatternMatcher::Pattern 
{
public:
    struct Hasher
    {
        std::size_t operator()(const Pattern& pattern) const
        {
            boost::hash<unsigned long long> hash;
            return hash(pattern.get_id());
        }
    };
public:
    Pattern(const unsigned long long& id, 
            const std::string& pattern,
            Bin* bin);
    Pattern(const Pattern& orig);
    virtual ~Pattern();
    
    const unsigned long long& get_id() const;
    unsigned long long get_id();
    
    const Bin* get_bin() const;
    Bin* get_bin();
    
    //Operators 
    Pattern& operator=(const Pattern& rhs);
    bool operator==(const std::string& rhs) const;
    bool operator!=(const std::string& rhs) const;
    bool operator==(const unsigned long long& rhs) const;
    bool operator!=(const unsigned long long& rhs) const;
    bool operator==(const Pattern& rhs) const;
    bool operator!=(const Pattern& rhs) const;
    bool operator<(const Pattern& rhs) const;
    
    friend std::ostream& operator<<(std::ostream& stream, Pattern& pattern)
    {
        return stream << "{\"id\": \"" << pattern.get_id() 
                      << "\", \"pattern\": \"" << pattern.get_value()
                      << "\", \"bin\": \"" << *pattern.get_bin()
                      << "\"}";
    }
private:
    unsigned long long __id;
    Bin* __bin;
};

} /* namespace Sorter */

#endif /* PATTERN_HPP */

