#pragma once

#include <vector>
#include "Dendrite.hpp"
#include "DataSet.hpp"

class Perceptron {
public:
    explicit Perceptron(double biais = 0.0);

    // Setters
    void addInput(Perceptron& input, double weight);


    // Getters
    double getOutput() const;
    const std::vector<Dendrite>& getDendrites() const;


    // Other

    const double calcInput(const DataSample &datasample) const;

    double activation(double z) const;
    double compute(const DataSample& datasample) const;

    double calcLogLoss(const DataSet &dataSet) const;
    std::vector<double> calcGradientW(const DataSet &dataSet) const;

// TODO (sylvain#1#11/26/25): Create class Gradient

    double calcGradientBiais(const DataSet &dataSet) const;
    void stepGradientDescent(DataSet &dataSet);


private:
    double m_biais;
    double m_output;  // Dimension = nbre de DataSample dans le dataSet en entrée
    double m_learningStep;
    std::vector<Dendrite> m_dendrites; //Dimension : Dimension des DataSample du DataSet en entrée (nb de neurones dans la couche précédente)
};
