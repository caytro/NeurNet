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
    std::vector<double>& getZ();  // S(Wk . Xk) + b  , size  = DataSet.samples.size() = Un par échantillons
    std::vector<double>& getA();  // a(Z) ,  size(A) = size(Z)
    std::vector<double>& getE();  // A - Y , size(E) = size(A)
    std::vector<double>& getGradientW();  // S(ek . Xk) , Somme sur les échantillons, size == m_dendrites.size()


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
    std::vector<double> m_gradient;
    double m_learningRate;
    std::vector<Dendrite> m_dendrites; //Dimension : Dimension des DataSample du DataSet en entrée (nb de neurones dans la couche précédente)
};
