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

#include <experimental/filesystem>
#include <iomanip>
#include <podofo/podofo.h>
#include <sstream>

namespace fs = std::experimental::filesystem;

namespace Pdf {
    namespace Splitter { 
        namespace Services { 
            
            PdfSplitter::PdfSplitter(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::Splitter::Models::Job>>>& t_jobs,
                    const std::string& t_output_directory)
              : m_jobs(t_jobs), 
                m_output_directory(t_output_directory),
                m_notifier(nullptr) {
            }
            
            PdfSplitter::PdfSplitter(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::Splitter::Models::Job>>>& t_jobs,
                    const std::string& t_output_directory,
                    const std::shared_ptr<Notifier::INotifier>& t_notifier) 
              : m_jobs(t_jobs), 
                m_output_directory(t_output_directory),
                m_notifier(t_notifier) {
                notify("PdfSplitter::PdfSplitter()");
            }

            bool 
            PdfSplitter::process() {
                notify("PdfSplitter::process()");

                auto job = std::move(m_jobs->pop());
                if (fs::exists(job->filename)) {
                    PoDoFo::PdfMemDocument input_document;

                    input_document.Load(job->filename.c_str());
                    fs::path filename(job->filename);

                    for (int i = 0; i < input_document.GetPageCount(); ++i) {
                        std::stringstream ss;
                        ss << m_output_directory
                           << filename.filename().stem().string() << "_"
                           << std::setw(4) << std::setfill('0') << (i + 1)
                           << ".pdf"; 
                        
                        PoDoFo::PdfMemDocument output_document;
                        output_document.InsertExistingPageAt(input_document, i, output_document.GetPageCount());
                        output_document.Write(ss.str().c_str());
                    }
                }

                return true;
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