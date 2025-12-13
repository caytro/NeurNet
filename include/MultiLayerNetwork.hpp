#pragma once
#include "Layer.hpp"
#include "NeurNetDefs.hpp"

#include <vector>


class MultiLayerNetwork {
public:

// Constructor

    MultiLayerNetwork(std::vector<size_t> nbNeuronesPerLayer,
                      size_t inputDimension,
                      nn::Activation act);

// Setters

    void setInputDataSet(DataSet& dataSet);
    void appendLayer(size_t nbNeurones);
    // layer[0] est la couche d'entrée, Layer[nbLayer - 1] est la couche de sortie

// Getters

    DataSet& getInputDataSet();
    std::vector<Layer>& getLayers();
    DataSet& getOutputDataSet();


// Compute

    void forwardPropagation();
    void backPropagation();



private:
    size_t m_inputDimension;

    nn::Activation m_act;
    std::vector<Layer> m_layers;
    DataSet m_inputDataSet;


};
