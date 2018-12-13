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
                PoDoFo::PdfFont pdf_font;
                std::string text;
                
                TextResult() = default;

                bool operator==(const TextResult& rhs) const noexcept;
                bool operator!=(const TextResult& rhs) const noexcept;
                bool operator<(const TextResult& rhs) const noexcept;
                Job& operator=(const TextResult& rhs);
                Job& operator<<(const std::vector<std::string>& rhs);
                Job& operator<<(const boost::property_tree::ptree& rhs);

                boost::property_tree::ptree& 
                operator>>(boost::property_tree::ptree& lhs) const;
            };

        } /* namespace Models */
    } /* namespace TextExtractor */
} /* namespace Pdf */

#endif /* PDF_TEXTEXTRACTOR_MODELS_RESULT_H */

