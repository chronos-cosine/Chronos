/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Layer.cpp
 * Author: user
 * 
 * Created on 19 December 2018, 7:40 AM
 */

#include "Layer.h"

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            Layer<T>::Layer(uint16_t t_neuron_count,
                            const std::shared_ptr<IActivationFunction<T>>& t_activation_function, 
                            const std::shared_ptr<ILayer<T>>& t_previous_layer,
                            const std::shared_ptr<ILayer<T>>& t_next_layer) 
              : m_neuron_count(t_neuron_count),
                m_activation_function(t_activation_function),
                m_previous_layer(t_previous_layer), 
                m_next_layer(t_next_layer),
                m_weights(t_next_layer->get_neuron_count(), t_neuron_count + 1),
                m_values(t_neuron_count + 1) {
                m_values[t_neuron_count] = 1; //bias node
            }
            
            template <typename T>
            void 
            Layer<T>::set_value(const uint16_t& t_node_index, T value) {
                m_values[t_node_index] = std::move(value);
            }
            
            template <typename T>
            void 
            Layer<T>::activate() {
                for (uint16_t next_level_index = 0; 
                     next_level_index < m_next_layer->get_neuron_count();
                     ++next_level_index) {
                    for (uint16_t current_level_index = 0; 
                         current_level_index< m_neuron_count; 
                         ++current_level_index) {
                        
                    }
                }
                    
            }
              
            template <typename T>
            uint16_t 
            Layer<T>::get_neuron_count() {
                return m_neuron_count;
            }
            
            template <typename T>
            std::shared_ptr<IActivationFunction<T>>
            Layer<T>::get_activation_function() {
                return m_activation_function;
            }
            
            template <typename T>
            std::shared_ptr<ILayer<T>> 
            Layer<T>::get_next_layer() {
                return m_next_layer;
            }
            
            template <typename T>
            std::shared_ptr<ILayer<T>> 
            Layer<T>::get_previous_layer() {
                return m_previous_layer;
            } 
            
            template class Layer<float>;
            template class Layer<double>;
            
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */
