/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/ResultFileWriter.h"

/* 
 * File:   ResultFileWriter.cpp
 * Author: user
 * 
 * Created on 10 October 2018, 11:00 AM
 */

#include "Sorter/Bin.h"
#include "Sorter/Job.h"
#include "Sorter/Pattern.h"
#include "Core/Exception.h"

#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <map>
#include <set>
#include <string>
#include <sstream>

namespace Sorter {

    ResultFileWriter::ResultFileWriter() { }

    ResultFileWriter::~ResultFileWriter() { }
    
    boost::property_tree::ptree
    ResultFileWriter::read_job_file(const Job& job) {
        boost::property_tree::ptree ptree;
        std::ifstream file(job.get_filename());
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();

            boost::property_tree::read_json(buffer, ptree);
        } else {
            thrower ("Could not open job file.");
        }

        return ptree;
    }
    
    void 
    ResultFileWriter::write(const Job& job,
                            const std::map<std::shared_ptr<Pattern>, std::set<unsigned long long>>& patterns,
                            const std::set<std::shared_ptr<Bin>>& bins,
                            const std::string& output_directory) {
        boost::property_tree::ptree ptree;
        boost::property_tree::ptree ptree_matches;
        std::shared_ptr<Bin> prev_bin(nullptr);
        std::ofstream ofile;
        std::ifstream ifile;
        for (auto& pattern: patterns) {
            if (bins.find(pattern.first->get_bin()) != bins.end()) {
                if (prev_bin != pattern.first->get_bin()) {
                    if (ofile.is_open()) { 
                        ptree.add_child("PatternMatches", ptree_matches);
                        boost::property_tree::write_json(ofile, ptree);
                        ofile.close();
                    }

                    std::stringstream ss;
                    ss << output_directory << job.get_id() << "_" 
                       << pattern.first->get_bin()->get_id() << ".sdone"; 
                    ofile.open(ss.str().c_str());
                    ptree = read_job_file(job);
                    ptree_matches = boost::property_tree::ptree();
                }
                boost::property_tree::ptree ptree_pattern;
                ptree_pattern << *pattern.first;
                ptree_matches.add_child("Pattern", ptree_pattern);
                boost::property_tree::ptree positions;
                for (auto& index: pattern.second) {
                    boost::property_tree::ptree value;
                    value.put("", index);
                    positions.push_back(std::make_pair("", value));
                }
                ptree_matches.add_child("Positions", positions);
                prev_bin = pattern.first->get_bin();
            }
        }
        
        if (ofile.is_open()) {
            ptree.add_child("PatternMatches", ptree_matches);
            boost::property_tree::write_json(ofile, ptree);
            ofile.close();
        }
    }
     
} /* namespace Sorter */
