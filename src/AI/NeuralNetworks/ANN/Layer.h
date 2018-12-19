/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Layer.h
 * Author: user
 *
 * Created on 19 December 2018, 7:40 AM
 */

#ifndef LAYER_H
#define LAYER_H

#include <boost/numeric/ublas/matrix.hpp>
#include <memory>

#include "AI/NeuralNetworks/ANN/ILayer.h"

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
             
            template <typename T = double>
            class Layer : public ILayer<T> {
            public:
                virtual ~Layer() = default;
                Layer(uint16_t t_neuron_count,
                      const std::shared_ptr<IActivationFunction<T>>& t_activation_function,
                      const std::shared_ptr<ILayer<T>>& t_previous_layer,
                      const std::shared_ptr<ILayer<T>>& t_next_layer);
            public:
                virtual uint16_t get_neuron_count();
                virtual std::shared_ptr<IActivationFunction<T>> get_activation_function();
                virtual std::shared_ptr<ILayer<T>> get_next_layer();
                virtual std::shared_ptr<ILayer<T>> get_previous_layer();
                virtual void set_value(const uint16_t& t_node_index, T value);
                virtual void activate();
            private:
                uint16_t m_neuron_count;
                std::shared_ptr<ILayer<T>> m_next_layer;
                std::shared_ptr<ILayer<T>> m_previous_layer;
                std::shared_ptr<IActivationFunction<T>> m_activation_function;
                boost::numeric::ublas::matrix<T> m_weights;
                boost::numeric::ublas::vector<T> m_values;
            };
            
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* LAYER_H */

