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

#include "Services/CsvFileDataRepository.h"

#include <iostream>
#include <memory>
#include <thread>

int main(int argc, char** argv) {
    std::cout << "Starting Chronos-Sorter..." << std::endl;
    std::shared_ptr<Sorter::Services::IDataRepository> dr = 
            std::make_shared<Sorter::Services::CsvFileDataRepository>("./bins.dat", "./patterns.dat");
    
    
    return 0;
}