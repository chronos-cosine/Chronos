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
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <thread>
 
#include "Core/ConcurrentQueue.h"
#include "Core/FileSpooler.h"
#include "Sorter/Bin.h"
#include "Sorter/BinCsvFileReader.h"
#include "Sorter/Job.h"
#include "Sorter/JobFileReader.h" 
#include "Sorter/Pattern.h"
#include "Sorter/PatternBinLinker.h"
#include "Sorter/PatternCsvFileReader.h"
#include "Sorter/ResultFileWriter.h"

static std::map<unsigned long long, std::shared_ptr<Sorter::Bin>> bins;
static std::map<unsigned long long, std::shared_ptr<Sorter::Pattern>> patterns;
static std::shared_ptr<Sorter::Job> job = nullptr;
static Core::ConcurrentQueue<boost::filesystem::path> concurrent_queue;

static void test_job_file_reader() { 
    std::cout << "TESTING JOB FILE READER " << std::endl;
    Sorter::JobFileReader job_file_reader;
    job = job_file_reader.read("/home/user/stest.sjobd");
    std::cout << job->get_id() << std::endl;
    
}

static void test_bin_file_reader() { 
    std::cout << "TESTING BIN FILE READER " << std::endl;
    Sorter::BinCsvFileReader bin_file_reader;
    bins = bin_file_reader.read("/home/user/bins.dat");
    
    for (auto& pair: bins) {
        std::cout << "ID: " << pair.first << " Bin: " << *pair.second << std::endl;
    }
}

static void test_pattern_file_reader() {
    std::cout << "TESTING PATTERN FILE READER " << std::endl;
    Sorter::PatternCsvFileReader pattern_file_reader;
    patterns = pattern_file_reader.read("/home/user/patterns.dat");
    
    for (auto& pair: patterns) {
        std::cout << "ID: " << pair.first << " Pattern: " << *pair.second << std::endl;
    }
    
}

static void test_pattern_bin_linking() {
    Sorter::PatternBinLinker pattern_bin_linker;
    pattern_bin_linker.link(patterns, bins);
    
    for (auto& pair: patterns) {
        std::cout << "ID: " << pair.first << " Pattern: " << *pair.second << std::endl;
    }
}

static void test_result_file_writer() { 
    std::cout << "TESTING RESULT FILE WRITER " << std::endl; 
    Sorter::ResultFileWriter result_file_writer;
    std::map<std::shared_ptr<Sorter::Pattern>, std::set<unsigned long long>> results;
    std::set<unsigned long long> positions;
    positions.insert(34);
    positions.insert(23);
    positions.insert(2323);
    positions.insert(232323);
    results[patterns.begin()->second] = positions;
    result_file_writer.write(*job, results);
}

static void test_file_spooler() {
    std::cout << "TESTING FILESPOOLER " << std::endl; 
    Core::FileSpooler filespooler("/home/user/", ".sjob", concurrent_queue);
    std::thread ts([&](Core::FileSpooler* fs) { fs->start(); fs->stop(); }, &filespooler);
    ts.detach();
    
    std::thread t2([&](Core::ConcurrentQueue<boost::filesystem::path>* cq) {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            auto item = cq->pop();
            std::cout << "Popped: " <<  item << std::endl;
            if (cq->size() == 0) break;
        }
    }, &concurrent_queue);
    t2.detach();
    
    while (true) {
        std::cout << concurrent_queue.size() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
            if (concurrent_queue.size() == 0) break;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
//    test_bin_file_reader();
//    test_job_file_reader();
    test_pattern_file_reader();
//    test_pattern_bin_linking();
//    test_result_file_writer();
    
 //   test_file_spooler();
    
    return 0;
}