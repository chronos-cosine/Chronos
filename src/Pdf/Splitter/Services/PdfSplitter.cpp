/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PdfSplitter.cpp
 * Author: user
 * 
 * Created on 04 December 2018, 11:29 AM
 */

#include "Pdf/Splitter/Services/PdfSplitter.h"

namespace Pdf {
    namespace Splitter { 
        namespace Services { 
            
            PdfSplitter::PdfSplitter(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::Splitter::Models::Job>>>& t_jobs)
              : m_jobs(t_jobs), 
                m_notifier(nullptr) {
            }
            
            PdfSplitter::PdfSplitter(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::Splitter::Models::Job>>>& t_jobs,
                const std::shared_ptr<Notifier::INotifier>& t_notifier) 
              : m_jobs(t_jobs), 
                m_notifier(t_notifier) {
                notify("PdfSplitter::PdfSplitter()");
            }

            bool 
            PdfSplitter::process() {
                return false;
            }
           
            void 
            PdfSplitter::notify(const std::string& t_message) {
                if (nullptr != m_notifier) {
                    m_notifier->notify(t_message);
                }
            }
             
        } /* namespace Models */
    } /* namespace Splitter */
} /* namespace Pdf */

