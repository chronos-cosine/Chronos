/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ILogisticFunction.h
 * Author: user
 *
 * Created on 21 December 2018, 6:43 AM
 */

#ifndef AI_NEURALNETWORKS_ANN_IACTIVATIONFUNCTION_H
#define AI_NEURALNETWORKS_ANN_IACTIVATIONFUNCTION_H
namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class IActivationFunction {
            public:
                virtual T f(T input) const = 0;
                virtual T f_derivative(T input) const = 0;
                
            }; /* class IActivationFunction */
            
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* AI_NEURALNETWORKS_ANN_IACTIVATIONFUNCTION_H */

