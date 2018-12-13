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

#include "Collections/ICollection.h"
#include "Geometry/Point.h"
#include "Notifier/Notifiable.h"
#include "Apps/Pdf/TextExtractor/Models/Job.h"
#include "Processors/ProcessorBase.h"

#include <memory>
#include <podofo/podofo.h> 

#ifndef MAX_PATH
#define MAX_PATH 512
#endif // MAX_PATH

namespace Pdf {
    namespace TextExtractor {
        namespace Services {
            
            class TextExtractor : public Processors::ProcessorBase,
                                  public Notifier::Notifiable {
            public:
                virtual ~TextExtractor() = default;
//                TextExtractor(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::TextExtractor::Models::Job>>>& t_jobs);
//                TextExtractor(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::TextExtractor::Models::Job>>>& t_jobs,
//                              const std::shared_ptr<Notifier::INotifier>& t_notifier);
            protected:
                virtual bool process();
            private: 
                void extract_text(PoDoFo::PdfMemDocument* pDocument, 
                                 PoDoFo::PdfPage* pPage ); 
                void add_text_element(const Geometry::Point& current_position, 
                                    PoDoFo::PdfFont* pCurFont, 
                                    const PoDoFo::PdfString& rString);
            private:
                std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::TextExtractor::Models::Job>>> m_jobs;
            }; /* class TextExtractor */
                    
        } /* namespace Services */
    } /* namespace TextExtractor */
} /* namespace Pdf */

#endif /* PDF_TEXTEXTRACTOR_SERVICES_TEXTEXTRACTOR_H */
