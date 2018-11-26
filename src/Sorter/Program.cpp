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

#include "Repositories/CsvFileDataRepository.h"
#include "Services/SortingMachine.h"

#include <chrono>
#include <experimental/filesystem>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

namespace fs = std::experimental::filesystem;

int main(int argc, char** argv) {
    std::cout << "Starting Chronos-Sorter..." << std::endl;
    
    Sorter::Repositories::CsvFileDataRepository repository(
                                                "./bins.dat", "./patterns.dat");
    auto data_context = repository.create_data_context();
    
    std::vector<fs::path> paths;
    paths.push_back("./1/");
    paths.push_back("./2/");
    
    Sorter::Services::SortingMachine sm(paths, 
                                        std::chrono::seconds(4), 
                                        1, 
                                        data_context);
    sm.start();
    while (sm.get_is_running()) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    
    return 0;
}