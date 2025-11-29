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
    double getLearningRate() const;
    std::vector<double>& getZ();  // S(Wk . Xk) + b  , size  = DataSet.samples.size() = Un par échantillons
    std::vector<double>& getA();  // a(Z) ,  size(A) = size(Z)
    std::vector<double>& getE();  // A - Y , size(E) = size(A)
    std::vector<double>& getGradientW();  // S(ek . Xk) , Somme sur les échantillons, size == m_dendrites.size()
    double getGradientB() const;
    double getBiais() const;

    // Other
    std::vector<double> getWVector() const;
    void calcZ(const DataSet& dataSet);
    void calcZ(); // Utilise dendrite.getSource().getA() en entrée
    void calcA();
    void calcE(const DataSet& dataSet);
    double calcLogLoss(const DataSet& dataSet) const;
    void calcGradientW(const DataSet& dataSet);
    void calcGradientB();
    double activationFunction(double z) const;
    void updateParams();

private:
    double m_biais;
    std::vector<double> m_z;
    std::vector<double> m_a;
    std::vector<double> m_e;
    std::vector<double> m_gradientW;
    double m_gradientB;
    double m_learningRate;
    std::vector<Dendrite> m_dendrites; //Dimension : Dimension des DataSample du DataSet en entrée (nb de neurones dans la couche précédente)
};
