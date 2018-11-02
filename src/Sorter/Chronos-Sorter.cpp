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
#include "Notifier/CoutNotifier.h"
#include "Notifier/INotifier.h"
#include "File/Spooler.h"
#include "Collections/ConcurrentQueue.h"

#include <iostream>
#include <memory>
#include <thread>
#include <string>

int main(int argc, char** argv) {
    std::cout << "\nStarting Chronos-Sorter..." << std::endl;
    std::shared_ptr<Sorter::Settings> settings = 
        File::JsonDataReader<Sorter::Settings>::read_shared("./Chronos-Sorter.settings");
    std::shared_ptr<Notifier::INotifier> notifier = std::make_shared<Notifier::CoutNotifier>();

    std::shared_ptr<Collections::ICollection<std::string>> collection = std::make_shared<Collections::ConcurrentQueue<std::string>>();
    
    File::Spooler spooler("./jobs/", ".sjob", ".sbusy", collection);
    
    std::thread t(&File::Spooler::start, 
                    std::ref(spooler));
    t.detach();
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    while (!collection->empty()) {
        
        std::cout << "INSIDE WHILE" << std::endl;
        std::string item = collection->pop();
        std::cout << item.c_str() << std::endl;
    } 
    
    std::cout << "\nExiting Chronos-Sorter..." << std::endl;
    return 0;
}