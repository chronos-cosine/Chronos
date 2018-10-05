/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Chronos-Sorter.cpp
 * Author: user
 *
 * Created on 04 October 2018, 7:08 AM
 */

#include <iostream>
#include <set>
 
#include "Sorter/Sorter.h"
#include "Sorter/Pattern.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    if (argc < 3)
    {
        std::cerr << "Incorrect number of parameters supplied" << std::endl;
        return 1;
    }
    
    Sorter::Sorter sorter(argv[1], argv[2]);
             
    return 0;
}

