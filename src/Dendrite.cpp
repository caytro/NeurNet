#include "Dendrite.hpp"
#include "Perceptron.hpp"


// Constructors

Dendrite::Dendrite(Perceptron& source, double weight)
    : m_source(source), m_weight(weight)
{}

// Setters

void Dendrite::setWeight(double weight){
    m_weight = weight;
}

// Getters

Perceptron& Dendrite::getSource() const {
    return m_source;
}

double Dendrite::getWeight() const {
    return m_weight;
}

