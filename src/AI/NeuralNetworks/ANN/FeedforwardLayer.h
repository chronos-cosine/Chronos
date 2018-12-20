/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FeedforwardLayer.h
 * Author: user
 *
 * Created on 20 December 2018, 7:30 AM
 */

#ifndef AI_NEURALNETWORKS_ANN_FEEDFORWARDLAYER_H
#define AI_NEURALNETWORKS_ANN_FEEDFORWARDLAYER_H

#include "AI/NeuralNetworks/ANN/IFeedforwardLayer.h"

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class FeedforwardLayer : public IFeedforwardLayer<T> {
            public:
                uint16_t get_neuron_count() const;
                uint16_t get_output_count() const;
                
                const std::shared_ptr<IActivationFunction<T>>& get_activation_function() const;
                const std::shared_ptr<ISummationFunction<T>>& get_summation_function() const;
                
                std::vector<std::shared_ptr<INeuron<T>>>& get_neurons();
                std::vector<std::shared_ptr<IWeight<T>>>& get_neuron_weights(const std::shared_ptr<INeuron<T>>& neuron);
                
                const std::vector<std::shared_ptr<INeuron<T>>>& activate() const;
            private:
                    
                
            }; /* class INeuron */
            
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* AI_NEURALNETWORKS_ANN_FEEDFORWARDLAYER_H */

