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

#include "AI/NeuralNetworks/ANN/IActivationFunction.h"
#include "AI/NeuralNetworks/ANN/INeuron.h"
#include "AI/NeuralNetworks/ANN/ISummationFunction.h"
#include "AI/NeuralNetworks/ANN/IWeight.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class IFeedforwardLayer {
            public:
                uint16_t get_neuron_count() const = 0;
                uint16_t get_output_count() const = 0;
                
                const std::shared_ptr<IActivationFunction<T>>& get_activation_function() const = 0;
                const std::shared_ptr<ISummationFunction<T>>& get_summation_function() const = 0;
                
                std::vector<std::shared_ptr<INeuron<T>>>& get_neurons() = 0;
                std::vector<std::shared_ptr<IWeight<T>>>& get_neuron_weights(const std::shared_ptr<INeuron<T>>& neuron) = 0;
                
                const std::vector<std::shared_ptr<INeuron<T>>>& activate() const = 0; 
                
            }; /* class INeuron */
            
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* AI_NEURALNETWORKS_ANN_IFEEDFORWARDLAYER_H */

