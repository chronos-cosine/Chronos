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

void completed(const void* sender, 
        const std::string& input ,
        const unsigned long long& total_matches) {
    std::cout << "COMPLETED!!\n"
              << "Sender: " << sender
              << "\nInput: " << &input
              << "\nMatches: " << total_matches << std::endl;
}
    
void match_found(const void* sender , 
            const std::string& input ,
            const unsigned long long& position ,
            const std::set<std::string>& patterns) { 
    std::cout << "MATCHES FOUND!!\n"
              << "Sender: " << sender
              << "\nInput: " << &input
              << "\nPosition: " << position << std::endl;
    for (auto& p : patterns) {
        std::cout << p << ", ";
    }
    std::cout << std::endl << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "\nStarting Chronos-Sorter..." << std::endl;
    std::set<std::string> patterns = {"he", "she", "his", "hers" };
    PatternMatchingMachine<> pm(patterns); 
    pm.completed = &completed;
    pm.match_found = &match_found;
    
    std::string input("This is a thest of ther her and he this she>.");
    pm.match(input, nullptr);
    
    std::cout << "\nExiting Chronos-Sorter..." << std::endl;
    return 0;
}
