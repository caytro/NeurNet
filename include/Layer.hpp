#pragma once
#include "Perceptron.hpp"

#include <vector>


class Layer
{

public:

// Constructors

    Layer();

// Setters

    void addNeurone(Perceptron& neurone);

// Getters
    std::vector<Perceptron>& getNeurones();

private:

    std::vector<Perceptron> m_neurones;


};
