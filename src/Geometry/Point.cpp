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
      : x(0), 
        y(0) {
    }
    
    Point::Point(const Point& t_point) 
      : x(t_point.x), 
        y(t_point.y) {
    }
    
    Point::Point(double t_x, double t_y)
      : x(t_x), 
        y(t_y) {
    }

    bool 
    Point::operator==(const Point& rhs) const noexcept {
        return x == rhs.x
               && y == rhs.y;
    }
    
    
    bool 
    Point::operator!=(const Point& rhs) const noexcept {
        return !(*this == rhs);
    }
    
    bool 
    Point::operator<(const Point& rhs) const noexcept {
        if (x != rhs.x) { 
            return x < rhs.x;
        }
        
        return y < rhs.y;
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
            
            boost::hash_combine<double>(seed, point.x);
            boost::hash_combine<double>(seed, point.y);
            
            return seed;
        }
    };
}
