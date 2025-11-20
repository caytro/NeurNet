#pragma once

#include <vector>
#include "Perceptron.hpp"



class Network {
public:
    Network() = default;

    Perceptron& addNeuron();
    Perceptron& addNeuron(double biais);


private:
    std::vector<Perceptron> m_layers;
};
