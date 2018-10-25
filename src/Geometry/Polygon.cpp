/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Geometry/Polygon.h"

/* 
 * File:   Polygon.cpp
 * Author: user
 * 
 * Created on 25 October 2018, 2:18 PM
 */

namespace Geometry {
     
    Polygon::Polygon()
        : __points(), __minimum_x(0), __minimum_y(0),
          __maximum_x(0), __maximum_y(0) {
    }
    
    Polygon::Polygon(const Polygon& other)
        : __points(other.__points), __minimum_x(0), 
          __minimum_y(0), __maximum_x(0), __maximum_y(0) {
        bool first = true;
        for (const auto& point: __points) {
            if (first) {
                __minimum_x = point.x;
                __minimum_y = point.y;
                __maximum_x = point.x;
                __maximum_y = point.y;
                first = false;
            } else {
                update_extremes(point);
            }
        }
    }
    
    Polygon::Polygon(const std::vector<Point>& points)
        : __points(points) {
        
    }
    
    Polygon::~Polygon() {
        
    }
    
    void 
    Polygon::update_extremes(const Point& point) {
        if (__maximum_x < point.x) {
            __maximum_x = point.x;
        }
        if (__maximum_y < point.y) {
            __maximum_y = point.y;
        }
        if (__minimum_x > point.x) {
            __minimum_x = point.x;
        }
        if (__minimum_y > point.y) {
            __minimum_y = point.y;
        }
    }

    void 
    Polygon::push(const Point& point) {
        __points.push_back(point);
        update_extremes(point);
    }
    
    void 
    Polygon::clear() {
        __points.clear();
        __minimum_x = 0;
        __minimum_y = 0;
        __maximum_x = 0;
        __maximum_y = 0;
    }
    
    double 
    Polygon::area() const {
        double area(0);
        Point last_point = *(--__points.end());
        
        for (const auto& point: __points) {
            area += (last_point.x + point.x) * (last_point.y - point.y);
            last_point = point;
        }
        
        return area / 2;
    }
    
    Point 
    Polygon::top_left() const {
        return Point(__minimum_x, __minimum_y);
    }
    
    Point 
    Polygon::bottom_right() const {
        return Point(__maximum_x, __maximum_y);
    }
    
    Size 
    Polygon::size() const {
        return Size(__maximum_x - __minimum_x, 
                    __maximum_y - __minimum_y);
    }
    
    std::vector<Point>::const_iterator 
    Polygon::begin() {
        return __points.begin();
    }
    
    std::vector<Point>::const_iterator 
    Polygon::end() {
        return __points.end();
    }
   
    bool 
    Polygon::operator==(const Polygon& rhs) {
        if (__points.size() != rhs.__points.size()) {
            return false;
        }
        
        for (int i = 0; i < rhs.__points.size(); ++i) {
            if (__points.at(i) != rhs.__points.at(i)) {
                return false;
            }
        }
        
        return true;
    }
    
    bool 
    Polygon::operator!=(const Polygon& rhs) { 
        return !(*this == rhs);
    }
    
    bool 
    Polygon::operator<(const Polygon& rhs) {
        return area() < rhs.area();
    }
    
    bool 
    Polygon::operator>(const Polygon& rhs) {
        return area() > rhs.area();
    }
    
}

