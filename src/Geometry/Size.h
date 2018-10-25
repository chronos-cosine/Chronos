/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Size.h
 * Author: user
 *
 * Created on 25 October 2018, 11:09 AM
 */

#ifndef GEOMETRY_SIZE_H
#define GEOMETRY_SIZE_H

#include <iostream>

namespace Geometry {
   
    struct Size {
        double width;
        double height;
        
        Size(const double& width, const double& height);
        Size(const Size& size);
        Size();
        
        double area() const;
        bool is_square() const;
        
        Size operator+(const Size& rhs) const;
        Size& operator+=(const Size& rhs);
        Size operator-(const Size& rhs) const;
        Size& operator-=(const Size& rhs);
        bool operator==(const Size& rhs) const;
        bool operator!=(const Size& rhs) const;
        bool operator<(const Size& rhs) const;
        bool operator>(const Size& rhs) const;
                
        friend std::ostream& operator<<(std::ostream& lhs, const Size& rhs);
    };

}

#endif /* GEOMETRY_SIZE_H */
