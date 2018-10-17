/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bin.h
 * Author: user
 *
 * Created on 04 October 2018, 12:19 PM
 */

#ifndef SORTER_BIN_H
#define SORTER_BIN_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <memory>
#include <mutex>
#include <string>
#include <set>

namespace Sorter {
    
    class Pattern;
    
    class Bin {
    private:
        std::set<std::shared_ptr<Pattern>> __patterns;
        unsigned long long __parent_id;
        unsigned long long __id;
        std::string __name;
        std::shared_ptr<Bin> __parent;
        std::mutex __mutex;
    public:
        Bin(const unsigned long long& id, 
            const std::string& name,
            const unsigned long long& parent_id);
        virtual ~Bin();

        //member functions
        const std::shared_ptr<Bin>& get_parent() const;
        void set_parent(const std::shared_ptr<Bin>& parent);
        const unsigned long long& get_id() const;
        const std::string& get_name() const;
        const unsigned long long& get_parent_id() const;
        std::set<std::shared_ptr<Pattern>>& get_patterns();
         
        //operators
        virtual bool operator==(const Bin& rhs) const;
        virtual bool operator!=(const Bin& rhs) const;
        virtual bool operator<(const Bin& rhs) const;
        virtual bool operator>(const Bin& rhs) const;

        //friend operators
        friend boost::property_tree::ptree& operator<<(boost::property_tree::ptree& lhs, const Bin& rhs);
        friend std::ostream& operator<<(std::ostream& lhs, const Bin& rhs);
        friend bool operator<(const std::shared_ptr<Bin>& lhs, const std::shared_ptr<Bin>& rhs);
        friend bool operator>(const std::shared_ptr<Bin>& lhs, const std::shared_ptr<Bin>& rhs);
        friend bool operator==(const std::shared_ptr<Bin>& lhs, const std::shared_ptr<Bin>& rhs);
        friend bool operator!=(const std::shared_ptr<Bin>& lhs, const std::shared_ptr<Bin>& rhs);
    public:
        struct Hasher {
            std::size_t operator()(const Bin& bin) const noexcept {
                return std::hash<unsigned long long>{}(bin.__id);
            }
        };
    public:
        Bin() = delete;
        Bin(Bin&) = delete;
        Bin(Bin&&) = delete;
        Bin& operator=(Bin&) = delete;
        Bin& operator=(Bin&&) = delete;
        
    }; /* class Bin */

} /* namespace Sorter */

#endif /* SORTER_BIN_H */

