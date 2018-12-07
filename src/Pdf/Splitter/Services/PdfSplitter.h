/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PdfSplitter.h
 * Author: user
 *
 * Created on 04 December 2018, 11:29 AM
 */

#ifndef PDF_SPLITTER_SERVICES_PDFSPLITTER_H
#define PDF_SPLITTER_SERVICES_PDFSPLITTER_H

#include "Collections/ICollection.h"
#include "Notifier/INotifier.h"
#include "Processors/ProcessorBase.h"
#include "Pdf/Splitter/Models/Job.h"

#include <memory>
#include <string>


namespace Pdf {
    namespace Splitter { 
        namespace Services { 
             
            class PdfSplitter : public Processors::ProcessorBase {
            public:
                virtual ~PdfSplitter() = default;
                PdfSplitter(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::Splitter::Models::Job>>>& t_jobs,
                            const std::string& t_output_directory); 
                PdfSplitter(const std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::Splitter::Models::Job>>>& t_jobs,
                            const std::string& t_output_directory,
                    const std::shared_ptr<Notifier::INotifier>& t_notifier); 
            protected:
                virtual bool process();
            private:
                void notify(const std::string& t_message);
            private:
                std::shared_ptr<Notifier::INotifier> m_notifier;
                std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::Splitter::Models::Job>>> m_jobs;
                std::string m_output_directory;
            };
            
        } /* namespace Models */
    } /* namespace Splitter */
} /* namespace Pdf */


#endif /* PDF_SPLITTER_SERVICES_PDFSPLITTER_H */

