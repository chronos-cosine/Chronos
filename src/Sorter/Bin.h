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
#include <mutex>
#include <string>

namespace Sorter {

    class Bin {
    public:
        struct Hasher {
            std::size_t operator()(const Bin& bin) const noexcept {
                return std::hash<unsigned long long>{}(bin.__id);
            }
        };
    public:
        Bin(const unsigned long long& id, 
            const std::string& name,
            const unsigned long long& parent_id);
        Bin(const Bin& orig);
        virtual ~Bin();

        //member functions
        Bin* get_parent() const;
        void set_parent(Bin* parent);
        const unsigned long long& get_id() const;
        const std::string& get_name() const;
        const unsigned long long& get_parent_id() const;
         
        //operators
        virtual Bin& operator=(const Bin& rhs);
        virtual bool operator==(const Bin& rhs) const;
        virtual bool operator!=(const Bin& rhs) const;
        virtual bool operator<(const Bin& rhs) const;
        virtual bool operator>(const Bin& rhs) const;

        //friend operators
        friend boost::property_tree::ptree& operator<<(boost::property_tree::ptree& lhs, const Bin& rhs);
    private:
        unsigned long long __parent_id;
        unsigned long long __id;
        std::string __name;
        Bin* __parent;
        std::mutex __mutex;
        
    }; /* class Bin */

} /* namespace Sorter */

#endif /* SORTER_BIN_H */

