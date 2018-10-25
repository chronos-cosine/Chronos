/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Geometry/Rectangle.h"

/* 
 * File:   Rectangle.cpp
 * Author: user
 * 
 * Created on 25 October 2018, 11:23 AM
 */

#include <boost/functional/hash.hpp>

namespace Geometry {

    Rectangle::Rectangle(const Point& point, const Size& size)
        : point(point), size(size) {
        
    }
    
    Rectangle::Rectangle(const Rectangle& rectangle)
        : point(rectangle.point), size(rectangle.size) {
        
    }
    
    Rectangle::Rectangle()
        : point(), size() {
    }
     
    double 
    Rectangle::area() const {
        return size.area();
    }
    
    bool
    Rectangle::is_square() const {
        return size.is_square();
    }
    
    bool 
    Rectangle::operator==(const Rectangle& rhs) const {
        return point == rhs.point
               && size == rhs.size;
    }
    
    bool 
    Rectangle::operator!=(const Rectangle& rhs) const {
        return !(*this == rhs);
    }
    
    bool 
    Rectangle::operator<(const Rectangle& rhs) const {
        return point < rhs.point
               && size < rhs.size;
    }
    
    bool 
    Rectangle::operator>(const Rectangle& rhs) const {
        return point > rhs.point
               && size > rhs.size;
    }
              
    std::ostream& 
    operator<<(std::ostream& lhs, const Rectangle& rhs) {
        lhs << "{\"x\": " 
                << rhs.point.x
                << ", \"y\": " 
                << rhs.point.y 
                << ", \"width\": " 
                << rhs.size.width
                << ", \"height\": " 
                << rhs.size.height
            << "}";
        
        return lhs;
    }

}

namespace std {
    template<>
    struct hash<Geometry::Rectangle> {
        std::size_t operator()(const Geometry::Rectangle& rectangle) const {
            std::size_t seed = 0;
            
            boost::hash_combine(seed, rectangle.point.x);
            boost::hash_combine(seed, rectangle.point.y);
            boost::hash_combine(seed, rectangle.size.width);
            boost::hash_combine(seed, rectangle.size.height);
            
            return seed;
        }
    };
}
