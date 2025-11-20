#include "Perceptron.hpp"
#include <numeric>

Perceptron::Perceptron(double bias)
    : m_bias(bias)
{}

void Perceptron::addInput(Perceptron& input, double weight) {
    m_dendrites.emplace_back(input, weight);
}

double Perceptron::calcInput() const {
    return std::transform_reduce(
        m_dendrites.begin(),
        m_dendrites.end(),
        m_bias,                         // valeur initiale = biais
        std::plus<>(),                  // opération de réduction
        [](const Dendrite& d) {         // transformation
            return d.getSource().getOutput() * d.getWeight();
        }
    );
}

double Perceptron::getOutput() const {
    return m_output;
}

void Perceptron::setOutput(double output) {
    m_output = output;
}

void Perceptron::compute() {
    m_output = activation(calcInput());
}

double Perceptron::activation(double x) const {
    return x > 0 ? 1.0 : 0.0;
}
