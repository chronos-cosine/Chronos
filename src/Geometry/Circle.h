/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circle.h
 * Author: user
 *
 * Created on 25 October 2018, 11:51 AM
 */

#ifndef GEOMETRY_CIRCLE_H
#define GEOMETRY_CIRCLE_H

#include "Geometry/Point.h"

#include <iostream>

namespace Geometry {
   
    struct Circle {
        Point center;
        double radius;
        
        Circle(const Point& c, const double& r);
        Circle(const Circle& circle);
        Circle();
        
        double area() const;
        double diameter() const;
        
        bool operator==(const Circle& rhs) const;
        bool operator!=(const Circle& rhs) const;
        bool operator<(const Circle& rhs) const;
        bool operator>(const Circle& rhs) const;
                
        friend std::ostream& operator<<(std::ostream& lhs, const Circle& rhs);
    };

}

#endif /* GEOMETRY_CIRCLE_H */

