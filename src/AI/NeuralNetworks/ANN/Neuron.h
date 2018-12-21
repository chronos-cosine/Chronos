/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Neuron.h
 * Author: user
 *
 * Created on 21 December 2018, 7:56 AM
 */

#ifndef AI_NEURALNETWORKS_ANN_NEURON_H
#define AI_NEURALNETWORKS_ANN_NEURON_H

#include "AI/NeuralNetworks/ANN/INeuron.h"

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class Neuron : public INeuron<T> {
            public:
                virtual T get_value() const;
                virtual bool set_value(const T& t_value);
            private:
                T m_value;
                
            }; /* class Neuron */
            
            template <typename T>
            T 
            Neuron<T>::get_value() const {
                return m_value;
            }
            
            template <typename T>
            void 
            Neuron<T>::set_value(const T& t_value) {
                if (t_value != m_value) {
                    m_value = t_value;
                }
            }
            
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* AI_NEURALNETWORKS_ANN_NEURON_H */

