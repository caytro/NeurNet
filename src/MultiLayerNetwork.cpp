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
    for(size_t numLayer = 0 ; numLayer < nbNeuronesPerLayer.size() ; ++numLayer)
    {
        Layer newLayer(nbNeuronesPerLayer[numLayer],
                       (numLayer==0 ? m_inputDimension : nbNeuronesPerLayer[numLayer-1]), act);
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
