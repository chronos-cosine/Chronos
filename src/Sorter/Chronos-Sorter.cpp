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
#include "Exceptions/Exception.h"
#include "Sorter/SortingMachine.h"
#include "Notifier/INotifier.h"
#include "Notifier/CoutNotifier.h"
#include "Notifier/LogFileNotifier.h"
#include "Sorter/StartupSettings.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <thread>

int main(int argc, char** argv) {
    std::map<std::string, std::string> arguments = Core::ArgumentReader::read(argc, argv);
    std::map<std::string, std::string>::const_iterator settings = arguments.find(std::string("-sf"));
    if (settings != arguments.end()) {
        Sorter::StartupSettings startup_settings(settings->second);
        Sorter::SortingMachine sorting_machine(
            startup_settings.get_patterns_file_location(), 
            startup_settings.get_bins_file_location(),
            startup_settings.get_job_file_directories(), 
            startup_settings.get_sorter_count(),
            startup_settings.get_results_directory(),
            startup_settings.get_sorter_trigger_extension(),
            startup_settings.get_sorter_busy_extension(),
            startup_settings.get_sorter_done_extension(),
            startup_settings.get_notifier());
        sorting_machine.start();
        
        while (true) { 
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
    else {
        std::cout << "\nCould not find settings file.  Exiting..." << std::endl;
        return 1;
    }
 
    return 0;
}
