/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SummationFunction.h
 * Author: user
 *
 * Created on 21 December 2018, 8:07 AM
 */

#ifndef AI_NEURALNETWORKS_ANN_SUMMATIONFUNCTION_H
#define AI_NEURALNETWORKS_ANN_SUMMATIONFUNCTION_H

#include "AI/NeuralNetworks/ANN/ISummationFunction.h"
#include "AI/NeuralNetworks/ANN/INeuron.h"
#include "AI/NeuralNetworks/ANN/IWeight.h"

#include <stdexcept>

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class SummationFunction : public ISummationFunction<T> {
            public:
                virtual T f(const std::vector<INeuron<T>>& t_neurons,
                            const std::vector<IWeight<T>>& t_neuron_weights) const;
            private:
                T m_value;
                
            }; /* class Neuron */
            
            template <typename T>
            T 
            SummationFunction::f(const std::vector<INeuron<T>>& t_neurons,
                                 const std::vector<IWeight<T>>& t_neuron_weights) {
                if (t_neuron_weights.size() < t_neurons.size()) {
                    throw std::out_of_range("t_neuron_weights supplied less than t_neurons supplied.");
                }
                
                T sum = 0;
                for (long unsigned int i = 0; i < t_neurons.size(); ++i) {
                   sum += t_neurons[i] * t_neuron_weights[i];
                }
                
                return sum;
            }
             
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */


#endif /* AI_NEURALNETWORKS_ANN_SUMMATIONFUNCTION_H */

