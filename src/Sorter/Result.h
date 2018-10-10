/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Result.h
 * Author: user
 *
 * Created on 10 October 2018, 10:28 AM
 */

#ifndef SORTER_RESULT_H
#define SORTER_RESULT_H

#include "Sorter/Job.h"
#include "Sorter/Pattern.h"

#include <map>
#include <set>

namespace Sorter {
    
    class Result {
    public:
        Result(Job* job, 
               std::map<Pattern*, std::set<unsigned long long>>* matches);
        virtual ~Result();
        
        //friend operators
        friend std::ostream& operator<<(std::ostream& lhs, const Result& rhs);
    private:
        Job* __job;
        std::map<Pattern*, std::set<unsigned long long>>* __matches;
    }; /* class Result */

} /* namespace Sorter */
#endif /* RESULT_H */

