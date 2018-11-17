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

#include "Data/Bins.h"

#include <iostream>
#include <thread>

int main(int argc, char** argv) {
    std::cout << "Starting Chronos-Sorter..." << std::endl;
    auto bins = Sorter::Data::Bins("./bins.dat");
    
    for (auto iter = bins.begin();
         iter != bins.end();
         ++iter) {
        std::cout << iter->id << std::endl;
    }
    
    return 0;
}