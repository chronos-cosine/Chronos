/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Program.cpp
 * Author: user
 *
 * Created on 03 December 2018, 7:58 AM
 */
//https://github.com/NickNaso/PoDoFo
//https://sourceforge.net/p/podofo/mailman/message/35788020/
  
#include "Notifier/INotifier.h"
#include "Notifier/CoutNotifier.h"
#include "Notifier/LogFileNotifier.h"
#include "Pdf/TextExtractor/Services/TextExtractingMachine.h"

#include <chrono>
#include <experimental/filesystem>
#include <iostream>
#include <memory>
#include <vector>


/*
 * 
 */
int main(int argc, char** argv) {
     std::shared_ptr<Notifier::INotifier> notifier = std::make_shared<Notifier::CoutNotifier>();
//    std::shared_ptr<Notifier::INotifier> notifier = std::make_shared<Notifier::LogFileNotifier>(
//            std::chrono::minutes(15),
//            "./logs/"); 
        
    std::cout << "Chronos-Pdf-TextExtractor..." << std::endl;
    std::vector<fs::path> paths;
    paths.push_back("./1/"); 
    
    std::chrono::seconds sleep_time(5);
    
    Pdf::TextExtractor::Services::TextExtractingMachine tem(paths, 
                                        sleep_time,
                                        1,
                                        "./output/",
                                        notifier);
    tem.start();
    while (tem.get_is_running()) {
        std::this_thread::sleep_for(sleep_time);
    }
    
    return 0;
}

