#include "MultiLayerNetwork.hpp"
#include "Perceptron.hpp"
#include "Layer.hpp"

#include <vector>
#include <algorithm>
#include <cassert>


using namespace std;
// Constructorss

MultiLayerNetwork::MultiLayerNetwork(){}

// Setters

void MultiLayerNetwork::setDataSet(DataSet& dataSet)
{
    m_dataSet = dataSet;
}

void MultiLayerNetwork::addLayer(Layer& layer)
{
    m_layers.push_back(layer);
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
;


}
Layer& MultiLayerNetwork::getOutputLayer()
{
    assert(m_layers.size() >= 2);
    return m_layers[m_layers.size() - 1];
}
// Layer& MultiLayerNetwork::getInputLayer();
// Layer& MultiLayerNetwork::getNthLayer(std::size_t numLayer);

