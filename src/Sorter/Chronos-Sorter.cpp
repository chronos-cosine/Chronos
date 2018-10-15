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

#include "Core/ArgumentReader.h"
#include "Core/Helpers.h" 
#include "Core/Exception.h"
#include "Sorter/SortingMachine.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    try { 
        std::map<std::string, std::string> arguments = Core::ArgumentReader::read(argc, argv); 

        std::vector<std::string> job_paths;
        job_paths.push_back(arguments[std::string("-j")]);
        
        Sorter::SortingMachine sorting_machine(
            arguments[std::string("-p")], 
            arguments[std::string("-b")],
            job_paths, 
            1);

        sorting_machine.start();
    } catch (Core::Exception& e) { 
        std::cout << Core::Exception::getErrorStack(e);
    }
    
    return 0;
}
