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

#include "File/JsonDataReader.h"
#include "Sorter/Settings.h"
#include "Sorter/SortingMachine.h"
#include "Sorter/Sorter.h"
#include "Notifier/LogFileNotifier.h"
#include "Notifier/NotifierBase.h"
#include "File/Spooler.h"
#include "Collections/ConcurrentQueue.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <string>

int main(int argc, char** argv) {
    std::cout << "Starting Chronos-Sorter..." << std::endl;
    
    std::shared_ptr<Sorter::Settings> settings = 
        File::JsonDataReader<Sorter::Settings>::read("./Chronos-Sorter.settings");
    std::shared_ptr<Notifier::NotifierBase> notifier
            = std::make_shared<Notifier::LogFileNotifier>(
                std::chrono::minutes(settings->log_file_reset_minutes),
                settings->log_file_directory);
    Sorter::SortingMachine sorting_machine(settings, notifier);
    sorting_machine.start();
        
    return 0;
}