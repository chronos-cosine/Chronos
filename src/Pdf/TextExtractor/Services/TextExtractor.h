/***************************************************************************
 *   Copyright (C) 2008 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef PDF_TEXTEXTRACTOR_SERVICES_TEXTEXTRACTOR_H
#define PDF_TEXTEXTRACTOR_SERVICES_TEXTEXTRACTOR_H

#include "Geometry/Point.h"

#include <map>
#include <podofo/podofo.h> 

#ifndef MAX_PATH
#define MAX_PATH 512
#endif // MAX_PATH


namespace Pdf {
    namespace TextExtractor {
        namespace Services {
            class TextExtractor {
            public:
                virtual ~TextExtractor() = default;
                TextExtractor() = default;

                void Init( const char* pszInput );
                std::map<Geometry::Point, std::string> data;

            private: 
                void ExtractText(PoDoFo::PdfMemDocument* pDocument, 
                                 PoDoFo::PdfPage* pPage ); 
                void AddTextElement(double dCurPosX, double dCurPosY, 
                                    PoDoFo::PdfFont* pCurFont, 
                                    const PoDoFo::PdfString& rString);
            }; /* class TextExtractor */
                    
        } /* namespace Services */
    } /* namespace TextExtractor */
} /* namespace Pdf */

#endif /* PDF_TEXTEXTRACTOR_SERVICES_TEXTEXTRACTOR_H */
