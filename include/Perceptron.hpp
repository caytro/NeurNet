#pragma once

#include <vector>
#include "Dendrite.hpp"

class Perceptron {
public:
    explicit Perceptron(double bias = 0.0);

    void addInput(Perceptron& input, double weight);
    double calcInput() const;
    double getOutput() const;
    void setOutput(double output); // Pour les neurones de la couche dentrée
    void compute();

private:
    double activation(double x) const;

private:
    double m_bias;
    double m_output = 0.0;
    std::vector<Dendrite> m_dendrites;
};
