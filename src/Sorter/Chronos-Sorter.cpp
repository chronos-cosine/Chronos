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

#include "File/JsonDataReader.h"
#include "Sorter/Settings.h"
#include "Sorter/SortingMachine.h"
#include "Sorter/Sorter.h"

#include <iostream>
#include <memory>
#include <string>

int main(int argc, char** argv) {
    std::cout << "\nStarting Chronos-Sorter..." << std::endl;
    std::shared_ptr<Sorter::Settings> settings = 
        File::JsonDataReader::read_shared<Sorter::Settings>("./Chronos-Sorter.settings");
    
    Sorter::Job job = File::JsonDataReader::read<Sorter::Job>("./1.sjob");
    Sorter::Sorter* sorter = nullptr;
    
    Sorter::SortingMachine sm(settings);
    sm.__matcher->match(job, sorter);
    
    std::cout << "\nExiting Chronos-Sorter..." << std::endl;
    return 0;
}