#pragma once

#include <vector>
#include "Perceptron.hpp"



class Network {
public:
    Network() = default;




private:
    std::vector<Perceptron> m_neurons;
};
