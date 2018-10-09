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
 
#include "Core/Notifier_cout.h"
#include "Sorter/Sorter.h"
#include "Sorter/Pattern.h"

/*
 * 
 */
int main(int argc, char** argv) {
    PatternMatcher::IPattern input("This is another test to test if her picks up!");
    
    if (argc < 3) {
        std::cerr << "Incorrect number of parameters supplied" << std::endl;
        return 1;
    }
    
    Core::Notifier_cout notifier;
    Sorter::Sorter sorter(argv[1], argv[2], &notifier);
    sorter.start();
             
    return 0;
}

