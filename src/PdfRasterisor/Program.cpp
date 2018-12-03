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

namespace fs = std::experimental::filesystem;

/*
 * 
 */
int main(int argc, char** argv) {
    std::cout << "Chronos-Pdf-Rasterisor..." << std::endl;
    
    std::string filename("/home/user/Documents/temp/pdf/De tijd/25/DeTijd_DeTijd_20181025_001.pdf");
    
    if (fs::exists(filename)) {
        PoDoFo::PdfMemDocument document(filename.c_str());
        for (int i = 0; i < document.GetPageCount(); ++i) {
            std::cout << "Looping through page " << i << std::endl;
            PoDoFo::PdfPage* page = document.GetPage(i);
            PoDoFo::PdfContentsTokenizer tok(page);
            const char* token = nullptr;
            PoDoFo::PdfVariant var;
            PoDoFo::EPdfContentsType type;
            while (tok.ReadNext(type, token, var)) {
                std::cout << token << std::endl;
                switch (type) {
                    case PoDoFo::ePdfContentsType_Keyword:
                        // process token: it contains the current command
                        //   pop from var stack as necessary
                        break;
                    case PoDoFo::ePdfContentsType_Variant:
                        // process var: push it onto a stack
                        break;
                    default:
                        // should not happen!
                        break;
                }
            }
        }
    }
    
    return 0;
}

