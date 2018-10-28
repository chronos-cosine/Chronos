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
 
#include "PatternMatchingMachine.h"
#include "Node.h"

#include <iostream>
#include <string>
#include <set>

using namespace PatternMatcher;

int main(int argc, char** argv) {
    std::cout << "\nStarting Chronos-Sorter..." << std::endl;
    std::set<std::string> patterns = {"he", "she", "his", "hers" };
    PatternMatchingMachine<> pm(patterns);
    
    std::cout << "\nExiting Chronos-Sorter..." << std::endl;
    return 0;
}
