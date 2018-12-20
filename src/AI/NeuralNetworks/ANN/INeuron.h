/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INeuron.h
 * Author: user
 *
 * Created on 20 December 2018, 6:55 AM
 */

#ifndef AI_NEURALNETWORKS_ANN_INEURON_H
#define AI_NEURALNETWORKS_ANN_INEURON_H

namespace AI {
    namespace NeuralNetworks {
        namespace ANN {
            
            template <typename T>
            class INeuron {
            public:
                virtual T get_value() const = 0;
                virtual void set_value(const T& t_value) = 0;
                
            }; /* class INeuron */
            
        } /* namespace ANN */
    } /* namespace NeuralNetworks */
} /* namespace AI */

#endif /* AI_NEURALNETWORKS_ANN_INEURON_H */

