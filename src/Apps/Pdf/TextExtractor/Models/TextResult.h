/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Result.h
 * Author: user
 *
 * Created on 13 December 2018, 11:12 AM
 */

#ifndef PDF_TEXTEXTRACTOR_MODELS_RESULT_H
#define PDF_TEXTEXTRACTOR_MODELS_RESULT_H

#include "Geometry/Point.h"

#include <map>
#include <string>

namespace Pdf {
    namespace TextExtractor { 
        namespace Models { 
             
            struct TextResult { 
                Geometry::Point point;
                int font_size;
                int page_number;
                std::string text;
            };

        } /* namespace Models */
    } /* namespace TextExtractor */
} /* namespace Pdf */

#endif /* PDF_TEXTEXTRACTOR_MODELS_RESULT_H */

