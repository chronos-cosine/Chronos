/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternMatchinMachineExample.cpp
 * Author: user
 *
 * Created on 21 September 2018, 1:06 PM
 */
 
#include <iostream>  
#include <set>
#include <string>

#include "Pattern.hpp"
#include "PatternMatchingMachine.hpp"

using namespace PatternMatcher;

struct Completed
{
    void operator()(PatternMatchingMachine<Pattern>* sender, const CompletedSignalArgs& e)
    {
        std::cout << "===============================" << std::endl;
        std::cout << "sender: " << sender << std::endl;
        std::cout << "Input: " << e.get_input() << std::endl;
        std::cout << "Matches: " << e.get_patterns_found() << std::endl;
        std::cout << "===============================" << std::endl;
    }
};

struct MatchFound
{
    void operator()(PatternMatchingMachine<Pattern>* sender, const MatchFoundSignalArgs<Pattern>& e)
    {
        std::cout << "===============================" << std::endl;
        std::cout << "sender: " << sender << std::endl;
        std::cout << "Input: " << e.get_input() << std::endl;
        std::cout << "Position: " << e.get_position() << std::endl;
        std::cout << "Matches: [";
        for (std::set<Pattern>::iterator iter = e.get_patterns()->begin();
             iter != e.get_patterns()->end();
             ++iter)
        {
            std::cout << (*iter).get_value() << ", ";
        }
        std::cout << "]" << std::endl;
        std::cout << "===============================" << std::endl;
    }
};
  
/*
 * 
 */
int 
main(int argc, char** argv) 
{ 
    MatchFound mf;
    Completed c; 
    std::string input = "This is a test to see if he or she picks up";
    
    std::set<Pattern> patterns;
    patterns.insert(Pattern("he"));
    patterns.insert(Pattern("she"));
    patterns.insert(Pattern("his"));
    patterns.insert(Pattern("hers"));
    
    PatternMatchingMachine<Pattern> pattern_matching_machine(patterns);
    pattern_matching_machine.match_found().connect(mf);
    pattern_matching_machine.completed().connect(c);
    pattern_matching_machine.match(input);
    
    return 0;
}

