/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ISortingResult.h
 * Author: user
 *
 * Created on 06 November 2018, 1:43 PM
 */

#ifndef SORTER_ISORTINGRESULT_H
#define SORTER_ISORTINGRESULT_H

namespace Sorter {

    struct ISortingResult { 
        std::shared_ptr<Job> job;
        
    };
    
} /* namespace Sorter */

#endif /* SORTER_ISORTINGRESULT_H */

