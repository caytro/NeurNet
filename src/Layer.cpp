#include "Layer.hpp"

#include <vector>


using namespace std;

// Constructors

Layer::Layer() {}


// Setters

void Layer::addNeurone(Perceptron& neurone)
{
    m_neurones.push_back(neurone);
}

// Getters

vector<Perceptron>& Layer::getNeurones()
{
    return m_neurones;
}
