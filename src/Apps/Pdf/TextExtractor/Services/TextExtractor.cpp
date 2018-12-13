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

#include "Geometry/Point.h"
#include "Apps/Pdf/TextExtractor/Services/TextExtractor.h"

#include <map>
#include <stack>

namespace Pdf {
    namespace TextExtractor {
        namespace Services {
            
//            TextExtractor::TextExtractor(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::TextExtractor::Models::Job>>>& t_jobs) 
//              : Notifier::Notifiable(),
//                m_jobs(t_jobs) {    
//            }
//            
//            TextExtractor::TextExtractor(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::TextExtractor::Models::Job>>>& t_jobs,
//                    const std::shared_ptr<Notifier::INotifier>& t_notifier) 
//              : Notifier::Notifiable(t_notifier),
//                m_jobs(t_jobs) {
//              
//                notify("TextExtractor::TextExtractor()");
//            }
//            
//            bool 
//            TextExtractor::process() {
//                notify("TextExtractor::process()");
//
//                auto job = std::move(m_jobs->pop());
//                 
//                PoDoFo::PdfMemDocument document; 
//                document.Load(job->filename.c_str());
//
//                int page_count = document.GetPageCount();
//                for(int i = 0; i < page_count; ++i) {
//                    PoDoFo::PdfPage* page = document.GetPage(i);
//
//                    extract_text(&document, page);
//                }
//                
//                return true;
//            }
//         
//            void 
//            TextExtractor::extract_text(PoDoFo::PdfMemDocument* document, 
//                                        PoDoFo::PdfPage* page) {
//                notify("TextExtractor::ExtractText()");
//                
//                const char* pszToken = NULL;
//                PoDoFo::PdfVariant var;
//                PoDoFo::EPdfContentsType eType;
//
//                PoDoFo::PdfContentsTokenizer tokenizer(page);
//
//                double dCurPosX = 0.0;
//                double dCurPosY = 0.0;
//                bool bTextBlock = false;
//                PoDoFo::PdfFont* pCurFont = NULL;
//
//                std::stack<PoDoFo::PdfVariant> stack;
//
//                while( tokenizer.ReadNext( eType, pszToken, var ) )
//                {
//                    if( eType == PoDoFo::ePdfContentsType_Keyword )
//                    {
//                        // support 'l' and 'm' tokens
//                        if( strcmp( pszToken, "l" ) == 0 || 
//                            strcmp( pszToken, "m" ) == 0 )
//                        {
//                            if( stack.size() == 2 )
//                            {
//                                dCurPosX = stack.top().GetReal();
//                                stack.pop();
//                                dCurPosY = stack.top().GetReal();
//                                stack.pop();
//                            }
//                            else
//                            {
//                                while( !stack.empty() )
//                                    stack.pop();
//                            }
//                        }
//                        else if( strcmp( pszToken, "BT" ) == 0 ) 
//                        {
//                            bTextBlock   = true;     
//                        }
//                        else if( strcmp( pszToken, "ET" ) == 0 ) 
//                        {
//                            if( !bTextBlock ) 
//                                fprintf( stderr, "WARNING: Found ET without BT!\n" );
//                        }
//
//                        if( bTextBlock ) 
//                        {
//                            if( strcmp( pszToken, "Tf" ) == 0 ) 
//                            {
//                                if( stack.size() < 2 )
//                                {
//                                    fprintf( stderr, "WARNING: Expects two arguments for 'Tf', ignoring\n" );
//                                    pCurFont = NULL;
//                                    continue;
//                                }
//
//                                stack.pop();
//                                PoDoFo::PdfName fontName = stack.top().GetName();
//                                PoDoFo::PdfObject* pFont = page->GetFromResources(PoDoFo::PdfName("Font"), fontName);
//                                if( !pFont ) 
//                                {
//                                    PODOFO_RAISE_ERROR_INFO(PoDoFo::ePdfError_InvalidHandle, "Cannot create font!" );
//                                }
//
//                                pCurFont = document->GetFont( pFont );
//                                if( !pCurFont )
//                                {
//                                    fprintf( stderr, "WARNING: Unable to create font for object %" PDF_FORMAT_INT64 " %" PDF_FORMAT_INT64 " R\n",
//                                             static_cast<PoDoFo::pdf_int64>( pFont->Reference().ObjectNumber() ),
//                                             static_cast<PoDoFo::pdf_int64>( pFont->Reference().GenerationNumber() ) );
//                                }
//                            }
//                            else if( strcmp( pszToken, "Tj" ) == 0 ||
//                                     strcmp( pszToken, "'" ) == 0 ) 
//                            {
//                                if( stack.size() < 1 )
//                                {
//                                    fprintf( stderr, "WARNING: Expects one argument for '%s', ignoring\n", pszToken );
//                                    continue;
//                                }
//
//                                add_text_element( dCurPosX, dCurPosY, pCurFont, stack.top().GetString() );
//                                stack.pop();
//                            }
//                            else if( strcmp( pszToken, "\"" ) == 0 )
//                            {
//                                if( stack.size() < 3 )
//                                {
//                                    fprintf( stderr, "WARNING: Expects three arguments for '%s', ignoring\n", pszToken );
//
//                                    while( !stack.empty() )
//                                        stack.pop();
//
//                                    continue;
//                                }
//
//                                add_text_element( dCurPosX, dCurPosY, pCurFont, stack.top().GetString() );
//                                stack.pop();
//                                stack.pop(); // remove char spacing from stack
//                                stack.pop(); // remove word spacing from stack
//                            }
//                            else if( strcmp( pszToken, "TJ" ) == 0 ) 
//                            {
//                                if( stack.size() < 3 )
//                                {
//                                    fprintf( stderr, "WARNING: Expects one argument for '%s', ignoring\n", pszToken );
//                                    continue;
//                                }
//
//                                PoDoFo::PdfArray array = stack.top().GetArray();
//                                stack.pop();
//
//                                for( int i=0; i<static_cast<int>(array.GetSize()); i++ ) 
//                                {
//                                    if( array[i].IsString() || array[i].IsHexString() )
//                                        add_text_element( dCurPosX, dCurPosY, pCurFont, array[i].GetString() );
//                                }
//                            }
//                        }
//                    }
//                    else if (eType == PoDoFo::ePdfContentsType_Variant)
//                    {
//                        stack.push(var);
//                    }
//                    else
//                    {
//                        // Impossible; type must be keyword or variant
//                        PODOFO_RAISE_ERROR(PoDoFo::ePdfError_InternalLogic);
//                    }
//                }
//            }
//
//            void 
//            TextExtractor::add_text_element(const Geometry::Point& current_position, 
//                            PoDoFo::PdfFont* pCurFont, 
//                            const PoDoFo::PdfString& rString ) {
//                if( !pCurFont ) 
//                {
//                    fprintf( stderr, "WARNING: Found text but do not have a current font: %s\n", rString.GetString() );
//                    return;
//                }
//
//                if( !pCurFont->GetEncoding() ) 
//                {
//                    fprintf( stderr, "WARNING: Found text but do not have a current encoding: %s\n", rString.GetString() );
//                    return;
//                }
//
//                PoDoFo::PdfString unicode = pCurFont->GetEncoding()->ConvertToUnicode( rString, pCurFont ); 
//
////                auto iter = data.find(pt);
////                if (iter != data.end()) {
////                    iter->second += unicode.GetStringUtf8();
////                } else {
////                    data[std::move(pt)] = unicode.GetStringUtf8();
////                }
//            }

        } /* namespace Services */
    } /* namespace TextExtractor */
} /* namespace Pdf */