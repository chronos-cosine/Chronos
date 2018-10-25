/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Geometry/Size.h"

/* 
 * File:   Size.cpp
 * Author: user
 * 
 * Created on 25 October 2018, 11:09 AM
 */

#include <boost/functional/hash.hpp>

namespace Geometry {
    
    Size::Size()
        : width(0), height(0) {
    }
    
    Size::Size(const Size& size)
        : width(size.width), height(size.height) {
        
    }
    
    Size::Size(const double& w, const double& h)
        : width(w), height(h) {
    }
    
    double
    Size::area() const {
        return width * height;
    }
    
    bool 
    Size::is_square() const {
        return width == height;
    }
        
    Size
    Size::operator+(const Size& rhs) const {
        return Size(width + rhs.width, height + rhs.height);
    }
    
    Size& 
    Size::operator+=(const Size& rhs) {
        width += rhs.width;
        height += rhs.height;
        
        return *this;
    }
    
    Size 
    Size::operator-(const Size& rhs) const {
        return Size(width - rhs.width, height - rhs.height);
    }
    
    Size& 
    Size::operator-=(const Size& rhs) {
        width -= rhs.width;
        height -= rhs.height;
        
        return *this;
    }
    
    bool 
    Size::operator==(const Size& rhs) const {
        return rhs.width == width
               && rhs.height == height;
    }
    
    
    bool 
    Size::operator!=(const Size& rhs) const {
        return !(*this == rhs);
    }
    
    bool 
    Size::operator<(const Size& rhs) const {
        return width < rhs.width
               && height < rhs.height;
    }
        
    bool 
    Size::operator>(const Size& rhs) const {
        return width > rhs.width
               && height > rhs.height;
    }
    
    std::ostream& 
    operator<<(std::ostream& lhs, const Size& rhs) {
        lhs << "{\"width\": " 
                << rhs.width
                << ", \"height\": " 
                << rhs.height 
            << "}";
        
        return lhs;
    }
}

namespace std {
    template<>
    struct hash<Geometry::Size> {
        std::size_t operator()(const Geometry::Size& size) const {
            std::size_t seed = 0;
            
            boost::hash_combine(seed, size.width);
            boost::hash_combine(seed, size.height);
            
            return seed;
        }
    };
}
