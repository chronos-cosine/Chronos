/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Geometry/Circle.h"

/* 
 * File:   Circle.cpp
 * Author: user
 * 
 * Created on 25 October 2018, 11:51 AM
 */

#include <boost/functional/hash.hpp>
#include <math.h>

namespace Geometry {
       
    Circle::Circle(const Point& c, const double& r)
        : center(c), radius(r) {
    }
    
    Circle::Circle(const Circle& circle) 
        : center(circle.center), radius(circle.radius) {
    }
    
    Circle::Circle()
        : center(), radius(0) {
    }
    
    double 
    Circle::area() const {
        return M_PI * radius * radius;
    }
    
    double 
    Circle::diameter() const {
        return radius * 2;
    }
    
    bool 
    Circle::operator==(const Circle& rhs) const {
        return rhs.center == center
               && rhs.radius == radius;
    }
        
    bool 
    Circle::operator!=(const Circle& rhs) const {
        return !(*this == rhs);
    }
        
    bool 
    Circle::operator<(const Circle& rhs) const {
        return radius < rhs.radius;
    }
        
    bool 
    Circle::operator>(const Circle& rhs) const {
        return radius > rhs.radius;
    }
           
    std::ostream& 
    operator<<(std::ostream& lhs, const Circle& rhs) {
        lhs << "{\"x\": " 
                << rhs.center.x
                << ", \"y\": " 
                << rhs.center.y
                << ", \"radius\": " 
                << rhs.radius
            << "}";
        
        return lhs;
    }

}

namespace std {
    template<>
    struct hash<Geometry::Circle> {
        std::size_t operator()(const Geometry::Circle& circle) const {
            std::size_t seed = 0;
            
            boost::hash_combine(seed, circle.center.x);
            boost::hash_combine(seed, circle.center.y);
            boost::hash_combine(seed, circle.radius);
            
            return seed;
        }
    };
}
