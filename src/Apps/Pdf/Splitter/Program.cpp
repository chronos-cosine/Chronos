/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Program.cpp
 * Author: user
 *
 * Created on 04 December 2018, 7:07 AM
 */
 
#include "Notifier/CoutNotifier.h"
#include "Notifier/LogFileNotifier.h"
#include "Apps/Pdf/Splitter/Services/SplittingMachine.h"

#include <chrono>
#include <experimental/filesystem>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
 
int main(int argc, char** argv) {
   std::shared_ptr<Notifier::INotifier> notifier = std::make_shared<Notifier::CoutNotifier>();
//    std::shared_ptr<Notifier::INotifier> notifier = std::make_shared<Notifier::LogFileNotifier>(
//            std::chrono::minutes(15),
//            "./logs/");
    notifier->notify("Starting Chronos-Pdf-Splitter...");
        
    std::vector<fs::path> paths;
    paths.push_back("./1/"); 
    
    std::chrono::seconds sleep_time(5);
    
    Pdf::Splitter::Services::SplittingMachine sm(paths, 
                                        sleep_time,
                                        1,
                                        "./output/",
                                        notifier);
    sm.start();
    while (sm.get_is_running()) {
        std::this_thread::sleep_for(sleep_time);
    }
    
    return 0;
}

