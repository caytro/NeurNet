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
        if(i > 0) // First layer will be connected to input neurones when setDataSet(dataSet)
        {
            newLayer.fullConnect(m_layers[i-1]);
        }
    }
}

// Setters

void MultiLayerNetwork::setInputDataSet(DataSet& dataSet)
{
    m_inputDataSet = dataSet;
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

void MultiLayerNetwork::appendLayer(size_t nbNeurones)
{
    Layer newLayer = Layer(nbNeurones);
    m_layers.push_back(newLayer);
    if(m_layers.size() > 1)
    {
        newLayer.fullConnect(m_layers[m_layers.size() - 2]);
    }
}

// Getters

DataSet& MultiLayerNetwork::getInputDataSet()
{
    return m_inputDataSet;
}

vector<Layer>& MultiLayerNetwork::getLayers()
{
    return m_layers;
}

DataSet& MultiLayerNetwork::getOutputDataSet()
{
    m_layers.end()->calcOutputDataSet();
    return m_layers.end()->getOutputDataSet();
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
    assert(m_inputDataSet.getSamples().size() > 0);
    assert(m_layers.size() > 0);


    if(m_layers.size() > 0)
    {
        DataSet& currentDataSet = m_inputDataSet;
        for(size_t i = 0 ; i < m_layers.size() ;  ++i)
        {
            m_layers[i].computeNeurones(currentDataSet);
            m_layers[i].calcOutputDataSet();
            currentDataSet = m_layers[i].getOutputDataSet();
        }
    }
}

void MultiLayerNetwork::backPropagation()
{

}
