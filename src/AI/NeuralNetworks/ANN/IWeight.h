/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IWeight.h
 * Author: user
 *
 * Created on 20 December 2018, 6:57 AM
 */

#ifndef AI_NEURALNETWORKS_ANN_IWEIGHT_H
#define AI_NEURALNETWORKS_ANN_IWEIGHT_H

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class IWeight {
            public:
                virtual T get_value() const = 0;
                virtual void set_value(const T& t_value) = 0;

            }; /* class IWeight */

        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* AI_NEURALNETWORKS_ANN_IWEIGHT_H */

