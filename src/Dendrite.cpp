#include "Dendrite.hpp"
#include "Perceptron.hpp"

Dendrite::Dendrite(Perceptron& source, double weight)
    : m_source(source), m_weight(weight)
{}

Perceptron& Dendrite::getSource() const {
    return m_source;
}

double Dendrite::getWeight() const {
    return m_weight;
}
