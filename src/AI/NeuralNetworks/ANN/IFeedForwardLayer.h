/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IFeedforwardLayer.h
 * Author: user
 *
 * Created on 20 December 2018, 7:01 AM
 */
 
#ifndef AI_NEURALNETWORKS_ANN_IFEEDFORWARDLAYER_H
#define AI_NEURALNETWORKS_ANN_IFEEDFORWARDLAYER_H

#include <memory>
#include <vector>

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class INeuron;
            template <typename T>
            class IActivationFunction;
            
            template <typename T>
            class IFeedForwardLayer {
            public:
                virtual const std::shared_ptr<IActivationFunction<T>>& get_activation_function() const = 0;
                virtual std::vector<std::shared_ptr<INeuron<T>>>& get_neurons() = 0;
                virtual std::vector<std::shared_ptr<INeuron<T>>> activate() const = 0; 
                
            }; /* class INeuron */
            
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* AI_NEURALNETWORKS_ANN_IFEEDFORWARDLAYER_H */

