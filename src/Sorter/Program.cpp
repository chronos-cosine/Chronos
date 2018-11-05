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

#include "Collections/ICollection.h"
#include "Collections/ConcurrentQueue.h"
#include "File/Spooler.h"
#include "Sorter/Job.h"

#include <iostream>
#include <thread>

int main(int argc, char** argv) {
    std::cout << "Starting Chronos-Sorter..." << std::endl;
    
    std::shared_ptr<Collections::ICollection<Sorter::Job>> collection
        = std::make_shared<Collections::ConcurrentQueue<Sorter::Job>>();
    File::Spooler<Sorter::Job> spooler("./2/",
                 ".sjob",".sbusy", std::chrono::seconds(5), collection);
    
    
    std::thread t([collection]() {
        while (true) {
            auto item = collection->pop();
            std::cout << item.id << std::endl;
        }
    });
    t.detach();
    spooler.start();
    
    return 0;
}