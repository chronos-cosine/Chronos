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

#include "Sorter/Job.h"
#include "Sorter/Pattern.h"
#include "Core/Exception.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <map>
#include <set>
#include <string>
#include <sstream>

namespace Sorter {

    ResultFileWriter::ResultFileWriter() { }

    ResultFileWriter::~ResultFileWriter() { }
        
    void 
    ResultFileWriter::write(const Job& job, 
                            const std::map<std::shared_ptr<Pattern>, std::set<unsigned long long>>& matches) {
        std::lock_guard<std::mutex> lock(__mutex);
        std::ifstream file(job.get_filename());
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();

            boost::property_tree::ptree ptree;
            boost::property_tree::read_json(buffer, ptree);
            file.close();
            boost::property_tree::ptree ptree_matches;
             
            for (auto& pair: matches) {
                boost::property_tree::ptree pattern;
                pattern << *pair.first;
                ptree_matches.add_child("Pattern", pattern);
                boost::property_tree::ptree positions;
                for (auto& i: pair.second) {
                    boost::property_tree::ptree value;
                    value.put("", i);
                    positions.push_back(std::make_pair("", value));
                }
                
                ptree_matches.add_child("Positions", positions);
            }
            ptree.add_child("PatternMatches", ptree_matches);
            
            std::ofstream output(job.get_filename());
            boost::property_tree::write_json(output, ptree);
        } else {
            thrower("Could not open job file.");
        }        
    }
     

} /* namespace Sorter */
