/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Point.h
 * Author: user
 *
 * Created on 25 October 2018, 10:32 AM
 */

#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H

#include <iostream>

namespace Geometry {
   
    struct Point {
        double x;
        double y;
        
        Point(double t_x, double t_y);
        Point(const Point& point);
        Point();
        
        bool operator==(const Point& rhs) const noexcept;
        bool operator!=(const Point& rhs) const noexcept;
        bool operator<(const Point& rhs) const noexcept;
        
        friend std::ostream& operator<<(std::ostream& lhs, const Point& rhs);
    };

}

#endif /* GEOMETRY_POINT_H */

