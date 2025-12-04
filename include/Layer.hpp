#pragma once
#include "Perceptron.hpp"
#include "DataSet.hpp"
#include <vector>


class Layer
{

public:

// Constructors

    explicit Layer(size_t nbNeurones);

// Setters



// Getters

    std::vector<Perceptron>& getNeurones();
    DataSet& getOutputDataSet();

// Connexion

    void fullConnect(Layer& layer);

// Compute

    void computeNeurones(const DataSet& dataSet);
    void calcOutputDataSet();

private:

    std::vector<Perceptron> m_neurones;
    DataSet m_outputDataSet;

};
