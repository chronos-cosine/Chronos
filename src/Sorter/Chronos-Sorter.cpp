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

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <thread>

int main(int argc, char** argv) {
    std::map<std::string, std::string> arguments = Core::ArgumentReader::read(argc, argv); 

    std::vector<std::string> job_paths;
    job_paths.push_back(arguments[std::string("-j")]);
    std::shared_ptr<Notifier::INotifier> notifier(new Notifier::LogFileNotifier(1, std::string("/home/user/logs/")));

    Sorter::SortingMachine sorting_machine(
        arguments[std::string("-p")], 
        arguments[std::string("-b")],
        job_paths, 
        1,
        arguments[std::string("-o")],
        std::string(".sjob"),
        std::string(".busy"),
        notifier);

    sorting_machine.start();
    while (true) { 
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
        
    return 0;
}
