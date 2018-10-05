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

#include <string>

namespace Sorter {

    class Bin {
        struct hash
        {
            std::size_t operator()(const Bin& bin) const noexcept
            {
                return std::hash<unsigned long long>{}(bin.__id);
            }
        };  /* struct Bin::hash */
    public:
        Bin(const unsigned long long& id, 
            const std::string& name,
            Bin* parent);
        Bin(const Bin& orig);
        virtual ~Bin();

        //member functions
        virtual Bin* get_parent() const;
        virtual const unsigned long long& get_id() const;
        virtual const std::string& get_name() const;
         
        //operators
        virtual bool operator==(const Bin& rhs) const;
        virtual bool operator!=(const Bin& rhs) const;
        virtual bool operator<(const Bin& rhs) const;
        virtual bool operator>(const Bin& rhs) const;

        //friend operators
        friend std::ostream& operator<<(std::ostream& lhs, const Bin& rhs);
    private:
        Bin* __parent;
        unsigned long long __id;
        std::string __name;
    }; /* class Bin */

} /* namespace Sorter */

#endif /* SORTER_BIN_H */

