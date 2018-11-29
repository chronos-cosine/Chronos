/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternlessBinDataProvider.h
 * Author: user
 *
 * Created on 29 November 2018, 7:39 AM
 */

#ifndef SORTER_SERVICES_DATAPROVIDERS_PATTERNLESSBINDATAPROVIDER_H
#define SORTER_SERVICES_DATAPROVIDERS_PATTERNLESSBINDATAPROVIDER_H

#include "Sorter/Data/DataContext.h"
#include "Sorter/Models/Bin.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Services/IDataProvider.h"

#include <memory>
#include <string>

namespace Sorter {
    namespace Services {
        namespace DataProviders {
                    
            class PatternlessBinDataProvider : public IDataProvider {
            public:
                virtual ~PatternlessBinDataProvider() = default;
                PatternlessBinDataProvider(
                    const std::shared_ptr<Sorter::Data::DataContext>& t_data_context);
                PatternlessBinDataProvider(
                    const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                    const std::shared_ptr<Notifier::INotifier>& t_notifier);
                virtual void process(const std::shared_ptr<Sorter::Models::Job>& t_job);
            private:
                void init(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context);
                void notify(const std::string& t_message);
            private:
                std::shared_ptr<Notifier::INotifier> m_notifier;
                std::set<std::shared_ptr<Sorter::Models::Bin>> m_bins;
            };

        } /* namespace DataProviders */
    } /* namespace Services */
} /* namespace Sorter */ 
#endif /* SORTER_SERVICES_DATAPROVIDERS_PATTERNLESSBINDATAPROVIDER_H */

