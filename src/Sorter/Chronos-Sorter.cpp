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
#include <iostream>
#include <map>
#include <set>
 
#include "Sorter/Bin.h"
#include "Sorter/BinCsvFileReader.h"
#include "Sorter/Job.h"
#include "Sorter/JobFileReader.h"
#include "Sorter/MemoryManagement.h"
#include "Sorter/Pattern.h"
#include "Sorter/PatternBinLinker.h"
#include "Sorter/PatternCsvFileReader.h"
#include "Sorter/ResultFileWriter.h"

static std::map<unsigned long long, Sorter::Bin*> bins;
static std::map<unsigned long long, Sorter::Pattern*> patterns;
static Sorter::Job* job = nullptr;

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
        std::cout << "ID: " << pair.first << " Bin: " << pair.second << std::endl;
    }
}

static void test_pattern_file_reader() {
    std::cout << "TESTING PATTERN FILE READER " << std::endl;
    Sorter::PatternCsvFileReader pattern_file_reader;
    patterns = pattern_file_reader.read("/home/user/patterns.dat");
    
    for (auto& pair: patterns) {
        std::cout << "ID: " << pair.first << " Pattern: " << pair.second << std::endl;
    }
    
}

static void test_pattern_bin_linking() {
    Sorter::PatternBinLinker pattern_bin_linker;
    pattern_bin_linker.link(patterns, bins);
    
    for (auto& pair: patterns) {
        std::cout << "ID: " << pair.first << " Pattern: " << pair.second << std::endl;
    }
}

static void test_result_file_writer() { 
    std::cout << "TESTING RESULT FILE WRITER " << std::endl; 
    Sorter::ResultFileWriter result_file_writer;
    std::map<Sorter::Pattern*, std::set<unsigned long long>> results;
    std::set<unsigned long long> positions;
    positions.insert(34);
    positions.insert(23);
    positions.insert(2323);
    positions.insert(232323);
    results[patterns.begin()->second] = positions;
    result_file_writer.write(*job, results);
}

static void test_memory_management() {
    
    std::cout << "TESTING MEMORY MANAGEMENT BINS " << std::endl;
    Sorter::MemoryManagement memory_management;
    memory_management.free_bins(bins);
    
    std::cout << "TESTING MEMORY MANAGEMENT PATTERNS " << std::endl; 
    memory_management.free_patterns(patterns);
    delete job;
}

/*
 * 
 */
int main(int argc, char** argv) {
    test_bin_file_reader();
    test_job_file_reader();
    test_pattern_file_reader();
    test_pattern_bin_linking();
    test_result_file_writer();
    
    test_memory_management();
    return 0;
}