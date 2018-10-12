/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BooleanOperator.h
 * Author: user
 *
 * Created on 12 October 2018, 12:26 PM
 */

#ifndef SORTER_BOOLEANOPERATOR_H
#define SORTER_BOOLEANOPERATOR_H

namespace Sorter { 
    enum BooleanOperator {
        OR = 1,
        NOT = 2,
        AND = 4
    };
    
    static BooleanOperator to_boolean_operator(int value) {
        switch (value) {
            case 1:
                return BooleanOperator::OR;
            case 2:
                return BooleanOperator::NOT;
            case 4:
                return BooleanOperator::AND;
            default:
                return BooleanOperator::OR;
        }
    }
}

#endif /* BOOLEANOPERATOR_H */

