/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileReader.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 9:58 PM
 */

#ifndef SORTER_SPOOLER_FILEREADER_H
#define SORTER_SPOOLER_FILEREADER_H

namespace Sorter {
    namespace Spoolers {
        class FileReader {
        public:
            FileReader();
            FileReader(const FileReader& orig);
            virtual ~FileReader();
        private:

        }; /* class FileReader */
        
    } /* namespace Spoolers */
} /* namespace Sorter */

        

#endif /* SORTER_SPOOLER_FILEREADER_H */

