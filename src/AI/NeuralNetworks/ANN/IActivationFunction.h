/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IActivationFunction.h
 * Author: user
 *
 * Created on 19 December 2018, 7:03 AM
 */

#ifndef AI_NEURALNETWORKS_ANN_IACTIVATIONFUNCTION_H
#define AI_NEURALNETWORKS_ANN_IACTIVATIONFUNCTION_H

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class IActivationFunction {
            public:
                virtual T f(T input) = 0;
            };
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* AI_NEURALNETWORKS_ANN_IACTIVATIONFUNCTION_H */

