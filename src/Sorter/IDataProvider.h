/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IDataProvider.h
 * Author: user
 *
 * Created on 06 November 2018, 1:30 PM
 */

#ifndef SORTER_IDATAPROVIDER_H
#define SORTER_IDATAPROVIDER_H

namespace Sorter {

    class IDataProvider {
        IDataProvider(const IDataProvider&) = delete;
    public:
        virtual ~IDataProvider() = default;
        IDataProvider() = default;
    };
    
} /* namespace Sorter */

#endif /* SORTER_IDATAPROVIDER_H */

