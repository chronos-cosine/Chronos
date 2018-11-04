/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter/Chronos-Sorter.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 October 2018, 10:52 PM
 */

#include "Sorter/Settings/SorterSettings.h"
#include "Sorter/SortingMachine.h"

#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Starting Chronos-Sorter..." << std::endl;
    Sorter::Settings::SorterSettings settings;
    Sorter::SortingMachine sm(settings);
    
    return 0;
}