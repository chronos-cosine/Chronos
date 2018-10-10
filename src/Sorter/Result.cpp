/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Result.cpp
 * Author: user
 * 
 * Created on 10 October 2018, 10:28 AM
 */

#include "Result.h"
#include <map>
#include <set>

namespace Sorter {
    
    Result::Result(Job* job, 
                   std::map<Pattern*, std::set<unsigned long long>>* matches) 
        : __job(job), __matches(matches) { }

    Result::~Result() { }

    //friend operators
    std::ostream& 
    operator<<(std::ostream& lhs, const Result& rhs) {
        lhs << "{\n\t\"Id\":\"" << rhs.__job->get_id()
            << "\",\n\t\"Document\":\"" << rhs.__job->get_document()
            << "\",\n\t\"Matches\":[";
        
        bool first_match = true;
        for (auto& pair: *rhs.__matches) {
            if (first_match) {
                first_match = false;
            }
            else { 
                lhs << ",";
            }
            lhs << "\n\t\t{\n\t\t\t\"Pattern\":" << *pair.first
                << ",\n\t\t\t\"Positions\":[";
            bool first_position = true;
            for (const unsigned long long& position: pair.second) {
                if (first_position) { 
                    first_position = false;
                } 
                else { 
                    lhs << ",";
                }
                lhs << position;
            }
            lhs << "]\n\t\t}";
        }
        
        lhs << "\n\t]\n}";
        
        return lhs;
    } 
}
