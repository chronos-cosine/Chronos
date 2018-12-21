/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FeedForwardLayer.h
 * Author: user
 *
 * Created on 21 December 2018, 7:14 AM
 */

#ifndef AI_NEURALNETWORKS_ANN_FEEDFORWARDLAYER_H
#define AI_NEURALNETWORKS_ANN_FEEDFORWARDLAYER_H

#include "AI/NeuralNetworks/ANN/IActivator.h"
#include "AI/NeuralNetworks/ANN/IFeedForwardLayer.h"
#include "AI/NeuralNetworks/ANN/INeuron.h"
#include "AI/NeuralNetworks/ANN/IWeight.h"
#include "IWeight.h"

#include <memory>

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class FeedForwardLayer : public IFeedForwardLayer<T> {
            public:
                virtual ~FeedForwardLayer() = default;
                FeedForwardLayer(long unsigned int t_neuron_count,
                                 const std::shared_ptr<IActivator<T>>& t_activator,
                                 const std::shared_ptr<IFeedForwardLayer<T>>& t_previous_layer,
                                 const std::shared_ptr<IFeedForwardLayer<T>>& t_next_layer);
            public:
                virtual const std::shared_ptr<IActivationFunction<T>>& get_activation_function(); 
                virtual std::vector<std::shared_ptr<INeuron<T>>>& get_neurons(); 
                virtual const std::vector<std::shared_ptr<INeuron<T>>>& activate() const;
            public:
                const std::shared_ptr<IFeedForwardLayer<T>>& get_previous_layer() const;
                const std::shared_ptr<IFeedForwardLayer<T>>& get_next_layer() const;
            private:
                std::vector<std::shared_ptr<INeuron<T>>> m_neurons;
                std::shared_ptr<IActivationFunction<T>> m_activation_function;
                std::shared_ptr<IFeedForwardLayer<T>> m_previous_layer;
                std::shared_ptr<IFeedForwardLayer<T>> m_next_layer;
                std::vector<std::shared_ptr<INeuron<T>>> m_output;
                std::vector<std::vector<IWeight<T>>> m_weights;
                
            }; /* class FeedForwardLayer */
            
            template <typename T>
            FeedForwardLayer<T>::FeedForwardLayer(
                    long unsigned int t_neuron_count,
                    const std::shared_ptr<IActivationFunction<T>>& t_activation_function,
                    const std::shared_ptr<IFeedForwardLayer<T>>& t_previous_layer,
                    const std::shared_ptr<IFeedForwardLayer<T>>& t_next_layer) 
              : m_neurons(t_neuron_count),
                m_activation_function(t_activation_function),
                m_previous_layer(t_previous_layer),
                m_next_layer(t_next_layer),
                m_output(t_next_layer->get_neurons().size()),
                m_weights(t_next_layer->get_neurons().size()) {
                
                for (long unsigned int i = 0; i < m_output.size(); ++i) {
                    m_weights[i] = std::move(std::vector<IWeight<T>>(t_neuron_count + 1));
                }
            }
            
            template <typename T>
            const std::shared_ptr<IActivationFunction<T>>&
            FeedForwardLayer<T>::get_activation_function() {
                return m_activation_function;
            }
            
            template <typename T>
            virtual std::vector<std::shared_ptr<INeuron<T>>>& 
            FeedForwardLayer<T>::get_neurons() {
                return m_neurons;
            }
            
            template <typename T>
            const std::vector<std::shared_ptr<INeuron<T>>>&
            FeedForwardLayer<T>::activate() {
                for (long unsigned int i = 0; i < m_output.size(); ++i) {
                    m_output[i] = std::move(
                        m_activation_function->activate(m_neurons, m_weights[i])
                    );
                }
                
                return m_output;
            }

        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* AI_NEURALNETWORKS_ANN_FEEDFORWARDLAYER_H */

