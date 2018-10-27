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
    Sorter::StartupSettingsFileReader startup_settings_file_reader;
    Sorter::StartupSettings startup_settings = 
            startup_settings_file_reader.read("/home/theunis/NetBeansProjects/Chronos-Build/bin/Chronos-Sorter.settings");
    Sorter::SortingMachine sorting_machine(startup_settings);
    sorting_machine.start();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
    return 0;
}
