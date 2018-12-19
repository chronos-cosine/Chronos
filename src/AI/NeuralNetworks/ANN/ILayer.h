/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ILayer.h
 * Author: user
 *
 * Created on 19 December 2018, 7:20 AM
 */

#ifndef AI_NEURALNETWORKS_ANN_ILAYER_H
#define AI_NEURALNETWORKS_ANN_ILAYER_H

#include <cstdint>
#include <memory>

#include "AI/NeuralNetworks/ANN/IActivationFunction.h"

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
             
            template <typename T = double>
            class ILayer {
            public: 
                virtual uint16_t get_neuron_count() = 0;
                virtual std::shared_ptr<IActivationFunction<T>> get_activation_function() = 0; 
                virtual std::shared_ptr<ILayer<T>> get_next_layer() = 0;
                virtual std::shared_ptr<ILayer<T>> get_previous_layer() = 0;
                virtual void set_value(const uint16_t& t_node_index, T value) = 0;
            };
            
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */



#endif /* AI_NEURALNETWORKS_ANN_ILAYER_H */

