#pragma once

#include <vector>
#include "Dendrite.hpp"
#include "DataSet.hpp"

class Perceptron {
public:
    explicit Perceptron(double biais = 0.0);

    // Setters
    void addInput(Perceptron& input, double weight);
    void setLearningRate(double learningRate);

    // Getters
    std::vector<Dendrite>& getDendrites();
    std::vector<double>& getOutput();
    double getLearningRate() const;

    // Other
    std::vector<double> getWVector() const;
    void calcZ(const DataSet& dataSet);
    void calcA();
    double calcLogLoss(const DataSet& dataSet) const;
    void calcE(DataSet& dataSet);
    void calcGradient(DataSet& dataSet);
    double activationFunction(double z) const;


private:
    double m_biais;
    double m_output;  // Dimension = nbre de DataSample dans le dataSet en entrée
    std::vector<double> m_z;
    std::vector<double> m_a;
    std::vector<double> m_e;
    double m_learningRate;
    std::vector<Dendrite> m_dendrites; //Dimension : Dimension des DataSample du DataSet en entrée (nb de neurones dans la couche précédente)
};
