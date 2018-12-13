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

#include "Notifier/LogFileNotifier.h"
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
    std::shared_ptr<Notifier::INotifier> notifier = std::make_shared<Notifier::LogFileNotifier>(
            std::chrono::minutes(15),
            "./logs/");
    notifier->notify("Starting Chronos-Sorter...");
    
    Sorter::Repositories::CsvFileDataRepository repository("./bins.dat", 
                                                           "./patterns.dat", 
                                                           notifier);
    
    auto data_context = repository.create_data_context();
    std::vector<fs::path> paths;
    paths.push_back("./1/");
    paths.push_back("./2/");
    paths.push_back("./3/");
    paths.push_back("./4/");
    
    std::chrono::seconds sleep_time(5);
    
    Sorter::Services::SortingMachine sm(paths, 
                                        sleep_time, 
                                        6, 
                                        data_context,
                                        notifier);
    sm.start();
    while (sm.get_is_running()) {
        std::this_thread::sleep_for(sleep_time);
    }
    
    return 0;
}