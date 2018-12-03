/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Program.cpp
 * Author: user
 *
 * Created on 03 December 2018, 7:58 AM
 */
//https://github.com/NickNaso/PoDoFo
//https://sourceforge.net/p/podofo/mailman/message/35788020/
 
#include <experimental/filesystem>
#include <iostream>
#include <podofo/podofo.h>
#include <string>

#include "TextExtractor.h"

namespace fs = std::experimental::filesystem;

/*
 * 
 */
int main(int argc, char** argv) {
    std::cout << "Chronos-Pdf-Rasterisor..." << std::endl;
    
    std::string filename("/home/user/Documents/temp/pdf/De tijd/25/DeTijd_DeTijd_20181025_001.pdf");
     
    if (fs::exists(filename)) {
        
        try {
            TextExtractor extractor;
            extractor.Init( filename.c_str() );
            
            for (auto& pair: extractor.data) {
                std::cout.precision(10);
                std::cout << std::fixed << pair.first << ": " << pair.second << std::endl << std::endl;
            }
        } catch( PdfError & e ) {
            fprintf( stderr, "Error: An error %i ocurred during processing the pdf file.\n", e.GetError() );
            e.PrintErrorMsg();
            return e.GetError();
        }
    }
    
    return 0;
}

