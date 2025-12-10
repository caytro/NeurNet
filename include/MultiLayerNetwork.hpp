#pragma once
#include "Perceptron.hpp"
#include "Layer.hpp"

#include <vector>


class MultiLayerNetwork {
public:

// Constructor

    explicit MultiLayerNetwork(std::vector<size_t> nbNeuronesParLayer);

// Setters

    void setInputDataSet(DataSet& dataSet);
    void appendLayer(size_t nbNeurones);
    // layer[0] est la couche d'entrée, Layer[nbLayer - 1] est la couche de sortie

// Getters

    DataSet& getInputDataSet();
    std::vector<Layer>& getLayers();
    DataSet& getOutputDataSet();
    Layer& getOutputLayer();
    Layer& getInputLayer();
    Layer& getNthLayer(std::size_t numLayer);

// Compute

    void forwardPropagation();
    void backPropagation();



private:
    DataSet m_inputDataSet;
    std::vector<Layer> m_layers;
    std::vector<Perceptron> m_inputNeurones; // N'ont pas de dendrite
    // les inputNeurones seront créés et connectés aux neurones de layer[0] au moment du setDataSet

};
