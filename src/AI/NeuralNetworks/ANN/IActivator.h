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

#include <memory>

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class INeuron;
            template <typename T>
            class IWeight;
            template <typename T>
            class ISummationFunction;
            template <typename T>
            class IActivationFunction;
            
            template <typename T>
            class IActivator {
            public:
                virtual const std::shared_ptr<ISummationFunction<T>>& get_summation_function() = 0;
                virtual const std::shared_ptr<ILogisticFunction<T>>& get_logistic_function() = 0;
                
                virtual INeuron<T> activate(
                    const std::vector<std::shared_ptr<INeuron<T>>>& t_neurons,
                    const std::vector<std::shared_ptr<IWeight<T>>>& t_weights) const = 0;
                
            }; /* class IActivationFunction */
            
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* AI_NEURALNETWORKS_ANN_IACTIVATIONFUNCTION_H */

