/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Geometry/Point.h"

/* 
 * File:   Point.cpp
 * Author: user
 * 
 * Created on 25 October 2018, 10:32 AM
 */

#include <boost/functional/hash.hpp>

namespace Geometry {
    
    Point::Point()
        : x(0), y(0) {
    }
    
    Point::Point(const Point& point) 
        : x(point.x), y(point.y) {
    }
    
    Point::Point(const double& _x, const double& _y)
        : x(_x), y(_y) {
    }
        
    Point
    Point::operator+(const Point& rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    
    Point& 
    Point::operator+=(const Point& rhs) {
        x += rhs.x;
        y += rhs.y;
        
        return *this;
    }
    
    Point 
    Point::operator-(const Point& rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    
    Point& 
    Point::operator-=(const Point& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        
        return *this;
    }
    
    bool 
    Point::operator==(const Point& rhs) const {
        return rhs.x == x
               && rhs.y == y;
    }
    
    
    bool 
    Point::operator!=(const Point& rhs) const {
        return !(*this == rhs);
    }
    
    bool 
    Point::operator<(const Point& rhs) const {
        return x < rhs.x
               && y < rhs.y;
    }
        
    bool 
    Point::operator>(const Point& rhs) const {
        return x > rhs.x
               && y > rhs.y;
    }
    
    std::ostream& 
    operator<<(std::ostream& lhs, const Point& rhs) {
        lhs << "{\"x\": " 
                << rhs.x 
                << ", \"y\": " 
                << rhs.y 
            << "}";
        
        return lhs;
    }
}

namespace std {
    template<>
    struct hash<Geometry::Point> {
        std::size_t operator()(const Geometry::Point& point) const {
            std::size_t seed = 0;
            
            boost::hash_combine(seed, point.x);
            boost::hash_combine(seed, point.y);
            
            return seed;
        }
    };
}
