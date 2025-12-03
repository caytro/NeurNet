#include "MultiLayerNetwork.hpp"
#include "Perceptron.hpp"
#include "Layer.hpp"

#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>


using namespace std;
// Constructorss

MultiLayerNetwork::MultiLayerNetwork(vector<size_t> nbNeuronesParLayer)
{
    m_layers.clear();
    for(size_t i = 0 ; i < nbNeuronesParLayer.size() ; ++i)
    {
        Layer newLayer(nbNeuronesParLayer[i]);
        m_layers.push_back(newLayer);
    }
}

// Setters

void MultiLayerNetwork::setDataSet(DataSet& dataSet)
{
    m_dataSet = dataSet;
    m_inputNeurones.clear();
    if(m_layers.size() > 0)
    {
        for(size_t i = 0 ; i < dataSet.getDimension() ; ++i)
        {
            Perceptron newInputNeurone;
            m_inputNeurones.push_back(newInputNeurone);
            for(Perceptron& neurone : m_layers[0].getNeurones())
            {
                neurone.addInput(newInputNeurone,1.0);
            }
        }
    }

}

void MultiLayerNetwork::addLayer(Layer& layer)
{
    m_layers.push_back(layer); // A changer : Les layers doivent être créées dans Network
    // ex addLayer(nbNeurones) -> OK à nettoyer
}

// Getters

DataSet& MultiLayerNetwork::getDataSet()
{
    return m_dataSet;
}

vector<Layer>& MultiLayerNetwork::getLayers()
{
    return m_layers;
}

vector<vector<double>> MultiLayerNetwork::getOutput(){
    // result[i][j] = output du neurone i pour le dataSample j

    if (m_layers.size() < 2)
    {
        return vector<vector<double>>(0);
    }
    vector<Perceptron> outputLayerNeurones = getOutputLayer().getNeurones();
    vector<vector<double>> result; // Pour chaque neurone, un vector<double> par dataSample
    result.reserve(outputLayerNeurones.size() * m_dataSet.getSamples().size());
    for(Perceptron& neurone : outputLayerNeurones)
    {
        result.push_back(neurone.getA());
    }
    return result;

}
Layer& MultiLayerNetwork::getOutputLayer()
{
    assert(m_layers.size() >= 2);
    return m_layers[m_layers.size() - 1];
}
Layer& MultiLayerNetwork::getInputLayer()
{
    assert(m_layers.size() > 0);
    return m_layers[0];
}

Layer& MultiLayerNetwork::getNthLayer(std::size_t numLayer)
{
    assert(m_layers.size() > numLayer);
    // First layer : m_layer[0]
    return m_layers[numLayer];
}

// Compute

void MultiLayerNetwork::forwardPropagation()
{
    assert(m_dataSet.getSamples().size() > 0);
    assert(m_layers.size() > 0);


    if(m_layers.size() > 0)
    {
        DataSet& currentDataSet = m_dataSet;
        for(size_t i = 0 ; i < m_layers.size() ;  ++i)
        {
            m_layers[i].computeNeurones(currentDataSet);
            m_layers[i].calcOutputDataSet();
            currentDataSet = m_layers[i].getDataSet();
        }
    }
}

