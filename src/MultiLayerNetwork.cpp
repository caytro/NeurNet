#include "MultiLayerNetwork.hpp"
#include "Layer.hpp"

#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>


using namespace std;
// Constructors

MultiLayerNetwork::MultiLayerNetwork(vector<size_t> nbNeuronesPerLayer, size_t inputDimension, nn::Activation act):
    m_inputDimension(inputDimension),
    m_act(act)

{
    for(size_t i = 0 ; i < nbNeuronesPerLayer.size() ; ++i)
    {
        Layer newLayer(nbNeuronesPerLayer[i],(i==0 ? inputDimension : nbNeuronesPerLayer[i-1]),1);
        m_layers.push_back(newLayer);
    }
}
// Setters


// Getters





// Compute

void MultiLayerNetwork::forwardPropagation()
{

}

void MultiLayerNetwork::backPropagation()
{

}
