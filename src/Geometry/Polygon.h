/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Polygon.h
 * Author: user
 *
 * Created on 25 October 2018, 2:18 PM
 */

#ifndef GEOMETRY_POLYGON_H
#define GEOMETRY_POLYGON_H

#include "Geometry/Point.h"
#include "Geometry/Size.h"

#include <vector>

namespace Geometry {
    
    class Polygon {
    private:
        std::vector<Point> __points;
        double __minimum_x;
        double __minimum_y;
        double __maximum_x;
        double __maximum_y;
    public:
        Polygon();
        Polygon(const Polygon& other);
        Polygon(const std::vector<Point>& points);
        virtual ~Polygon();
        
        void push(const Point& point);
        void clear();
        double area() const;
        Point top_left() const;
        Point bottom_right() const;
        Size size() const;
        
        std::vector<Point>::const_iterator begin();
        std::vector<Point>::const_iterator end();
        
        bool operator==(const Polygon& rhs);
        bool operator!=(const Polygon& rhs);
        bool operator<(const Polygon& rhs);
        bool operator>(const Polygon& rhs);
    private:
        void update_extremes(const Point& point);
    };

}

#endif /* GEOMETRY_POLYGON_H */

