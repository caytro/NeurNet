#include "Layer.hpp"
#include "DataSample.hpp"
#include "Perceptron.hpp"

#include <vector>


using namespace std;

// Constructors

Layer::Layer(size_t nbNeurones)
{
    m_neurones = vector<Perceptron>(0);
    for(size_t i = 0 ; i < nbNeurones ; ++i)
    {
        Perceptron newNeurone;
        m_neurones.push_back(newNeurone);
    }
}


// Setters



// Getters

vector<Perceptron>& Layer::getNeurones()
{
    return m_neurones;
}

DataSet& Layer::getOutputDataSet()
{
    return m_outputDataSet;
}

// Connexion

void Layer::fullConnect(Layer& layer)
{
    for(Perceptron& neurone1 : m_neurones)
    {
        for(Perceptron& neurone2 : layer.getNeurones())
        {
            neurone1.addInput(neurone2);
        }
    }

}
// Compute

void Layer::computeNeurones(const DataSet& dataSet)
{
    for(Perceptron& neurone : m_neurones)
    {
        neurone.compute(dataSet);
    }
}

void Layer::calcOutputDataSet()
{
    m_outputDataSet = DataSet(m_neurones.size());
    if(m_neurones.size() > 0)
    {
        for(size_t i = 0 ; i < m_neurones[0].getA().size() ; ++i)
        {
            vector<double> currentInput(0);
            for(size_t j = 0 ; j < m_neurones.size() ; ++j)
            {
                currentInput.push_back(m_neurones[j].getA()[i]);
            }
            m_outputDataSet.addSample(currentInput,0);
        }
    }
}
