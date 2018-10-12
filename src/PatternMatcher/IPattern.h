/* 
 * File:   RootNode.h
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_IPATTERN_H
#define PATTERNMATCHER_IPATTERN_H

#include <iostream>
#include <mutex>
#include <string>
 
namespace PatternMatcher
{
    class IPattern {
    public:
        struct Hasher {
            std::size_t operator()(const IPattern& pattern) const noexcept {
                return std::hash<std::string>{}(pattern.__value);
            }
        };
    public: 
        //constructors
        IPattern(const char* value);
        IPattern(const std::string& value); 
        IPattern(const IPattern& value);
        IPattern(const IPattern&& value); 
        virtual ~IPattern();

        //member functions
        virtual const std::string& get_value() const;
        virtual std::string::iterator begin();
        virtual std::string::const_iterator begin() const; 
        virtual std::string::iterator end();
        virtual std::string::const_iterator end() const;

        //operators
        virtual IPattern& operator=(const IPattern& rhs);
        virtual IPattern& operator=(const IPattern&& rhs);
        virtual IPattern& operator=(const std::string& rhs);
        virtual IPattern& operator=(const char* rhs);
        virtual bool operator==(const IPattern& rhs) const;
        virtual bool operator!=(const IPattern& rhs) const;
        virtual bool operator<(const IPattern& rhs) const;
        virtual bool operator>(const IPattern& rhs) const;

        //friend operators
        friend std::ostream& operator<<(std::ostream& lhs, const IPattern& rhs);
    protected:
        std::string __value;
        std::mutex __mutex;
        
    }; /* class IPattern */
    
} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_IPATTERN_H */