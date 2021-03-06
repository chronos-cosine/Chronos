/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternlessBinDataProvider.cpp
 * Author: user
 * 
 * Created on 29 November 2018, 7:39 AM
 */

#include "Apps/Sorter/Services/DataProviders/PatternlessBinDataProvider.h"
#include "Apps/Sorter/Data/DataContext.h"
#include "Apps/Sorter/Models/Bin.h"
#include "Apps/Sorter/Models/Job.h"
#include "Apps/Sorter/Models/Pattern.h"
#include "Apps/Sorter/Models/Result.h"

#include <memory>
#include <string>

namespace Sorter {
    namespace Services {
        namespace DataProviders {
            
            PatternlessBinDataProvider::PatternlessBinDataProvider(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context) 
              : Notifier::Notifiable() {
                init(t_data_context);
            }
            
            PatternlessBinDataProvider::PatternlessBinDataProvider(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                    const std::shared_ptr<Notifier::INotifier>& t_notifier) 
              : Notifier::Notifiable(t_notifier) {
                notify("PatternlessBinDataProvider::PatternlessBinDataProvider()");
                
                init(t_data_context);
            }
            
            void 
            PatternlessBinDataProvider::process(const std::shared_ptr<Sorter::Models::Job>& t_job) {
                notify("PatternlessBinDataProvider::process()");
                
                for (auto& bin: m_bins) {
                    auto result = std::make_shared<Sorter::Models::Result>();
                    std::shared_ptr<Sorter::Models::Pattern> pattern(nullptr);
                    result->job = t_job;
                    result->bin = bin;
                    result->pattern_matches[pattern].insert(0);
                    
                    t_job->results.insert(result);
                }
            }
             
            void 
            PatternlessBinDataProvider::init(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context) {
                notify("PatternlessBinDataProvider::init()");
                
                for (auto& pair: t_data_context->bins) {
                    if ((pair.second)->patterns.empty()) {
                        m_bins.insert(pair.second);
                    }
                }
            }
            
        } /* namespace DataProviders */
    } /* namespace Services */
} /* namespace Sorter */ 