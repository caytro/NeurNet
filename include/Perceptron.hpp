#pragma once

#include <vector>
#include "Dendrite.hpp"
#include "DataSet.hpp"

class Perceptron {
public:
    explicit Perceptron(double biais = 0.0);

    void addInput(Perceptron& input, double weight);
    double calcInput() const;
    double getOutput() const;
    void setOutput(double output); // Pour les neurones de la couche dentrée
    void compute();
    double calcLogLoss(DataSet &dataSet) const;
    double calcGradient(DataSet &dataSet) const;
    void stepGradientDescent(DataSet &dataSet);
private:
    double activation(double x) const;

private:
    double m_biais;
    double m_output;
    double m_learningStep;
    std::vector<Dendrite> m_dendrites;
};
