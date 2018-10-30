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

#include "Sorter/Settings.h"
#include "File/DataReader.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    std::cout << "\nStarting Chronos-Sorter..." << std::endl;
    
    Sorter::Settings settings = std::move(File::JsonDataReader::read<Sorter::Settings>("./Chronos-Sorter.settings"));
    std::cout << settings << std::endl;
    
    std::cout << "\nExiting Chronos-Sorter..." << std::endl;
    return 0;
}