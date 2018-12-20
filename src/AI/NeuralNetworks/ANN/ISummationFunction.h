/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ISummationFunction.h
 * Author: user
 *
 * Created on 20 December 2018, 6:49 AM
 */

#ifndef AI_NEURALNETWORKS_ANN_ISUMMATIONFUNCTION_H
#define AI_NEURALNETWORKS_ANN_ISUMMATIONFUNCTION_H

#include <vector>

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class ISummationFunction {
            public:
                virtual T f(const std::vector<T>& t_neuron_values,
                            const std::vector<T>& t_neuron_weights) const = 0;
                
            }; /* class ISummationFunction */
            
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* AI_NEURALNETWORKS_ANN_ISUMMATIONFUNCTION_H */

