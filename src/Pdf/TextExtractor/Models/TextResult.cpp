/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Result.cpp
 * Author: user
 * 
 * Created on 13 December 2018, 11:12 AM
 */

#include "Pdf/TextExtractor/Models/TextResult.h"


namespace Pdf {
    namespace TextExtractor { 
        namespace Models { 
              
            bool 
            TextResult::operator==(const TextResult& rhs) const noexcept {
                
            }
            
            bool 
            TextResult::operator!=(const TextResult& rhs) const noexcept {
                
            }
            
            bool 
            TextResult::operator<(const TextResult& rhs) const noexcept {
                
            }
            
            Job& 
            TextResult::operator=(const TextResult& rhs) {
                
            }
            
            Job& 
            TextResult::operator<<(const std::vector<std::string>& rhs) {
                
            }
            
            Job& 
            TextResult::operator<<(const boost::property_tree::ptree& rhs) {
                
            }
            

            boost::property_tree::ptree&  
            TextResult::operator>>(boost::property_tree::ptree& lhs) const {
                
            }
            
        } /* namespace Models */
    } /* namespace TextExtractor */
} /* namespace Pdf */