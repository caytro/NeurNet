#include "Perceptron.hpp"
#include <numeric>
#include <cmath>


Perceptron::Perceptron(double biais): m_biais(biais)
{}

void Perceptron::addInput(Perceptron& input, double weight) {
    m_dendrites.emplace_back(input, weight);
}

double Perceptron::calcInput() const {
    return std::transform_reduce(
        m_dendrites.begin(),
        m_dendrites.end(),
        m_biais,                         // valeur initiale = biais
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
    if (size(m_dendrites) > 0) // Sinon c'est un neurone d'entrée, il ne faut pas modifier m_output
    {
        m_output = activation(calcInput());
    }
}

double Perceptron::activation(double x) const {
    return 1/(1 + exp(-x));
}
