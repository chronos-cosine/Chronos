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
#include "File/JsonDataWriter.h"
#include "Notifier/CoutNotifier.h"

#include "Sorter/File/StartupSettingsFileReader.h"
#include "Sorter/Bin.h"
#include "Sorter/BooleanOperator.h"
#include "Sorter/Pattern.h"
#include "Sorter/StartupSettings.h"
#include "Sorter/SortingMachine.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <thread>

int main(int argc, char** argv) {
    std::map<std::string, std::string> arguments = Core::ArgumentReader::read(argc, argv);
    std::map<std::string, std::string>::const_iterator settings = arguments.find(std::string("-sf"));
    if (settings != arguments.end()) {
        Sorter::StartupSettingsFileReader startup_settings_file_reader;
        Sorter::StartupSettings startup_settings = startup_settings_file_reader.read(settings->second);
        Sorter::SortingMachine sorting_machine(startup_settings);
        sorting_machine.start();
        
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
    }
    else {
        std::cout << "\nCould not find settings file.  Exiting..." << std::endl;
        return 1;
    }
 
    return 0;
}
