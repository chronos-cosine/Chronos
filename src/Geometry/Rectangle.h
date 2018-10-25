/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rectangle.h
 * Author: user
 *
 * Created on 25 October 2018, 11:23 AM
 */

#ifndef GEOMETRY_RECTANGLE_H
#define GEOMETRY_RECTANGLE_H

#include "Point.h"
#include "Size.h"

#include <iostream>

namespace Geometry {

    struct Rectangle {
        Point point;
        Size size;
        
        Rectangle(const Point& point, const Size& size);
        Rectangle(const Rectangle& rectangle);
        Rectangle();
        
        double area() const;
        bool is_square() const;
        
        bool operator==(const Rectangle& rhs) const;
        bool operator!=(const Rectangle& rhs) const;
        bool operator<(const Rectangle& rhs) const;
        bool operator>(const Rectangle& rhs) const;
                
        friend std::ostream& operator<<(std::ostream& lhs, const Rectangle& rhs);
    };

}

#endif /* GEOMETRY_RECTANGLE_H */
