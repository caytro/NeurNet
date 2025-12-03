#pragma once
#include "Perceptron.hpp"
#include "Layer.hpp"

#include <vector>


class MultiLayerNetwork {
public:

// Constructor

    explicit MultiLayerNetwork(std::vector<size_t> nbNeuronesParLayer);

// Setters

    void setDataSet(DataSet& dataSet);
    void addLayer(Layer& layer);
    // layer[0] est la couche d'entrée, Layer[nbLayer - 1] est la couche de sortie

// Getters

    DataSet& getDataSet();
    std::vector<Layer>& getLayers();
    std::vector<std::vector<double>> getOutput();
    Layer& getOutputLayer();
    Layer& getInputLayer();
    Layer& getNthLayer(std::size_t numLayer);

// Compute

    void forwardPropagation();



private:
    DataSet m_dataSet;
    std::vector<Layer> m_layers;
    std::vector<Perceptron> m_inputNeurones; // N'ont pas de dendrite
    // les inputNeurones seront créés et connectés aux neurones de layer[0] au moment du setDataSet

};
