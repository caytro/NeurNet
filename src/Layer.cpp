#include "Layer.hpp"
#include "DataSample.hpp"
#include "Matrix.hpp"
#include "NeurNetDefs.hpp"

#include <vector>


using namespace std;

// Constructors

/* inputDataSetSize = Nombre d'échantillons dans le dataSet
  inputDataDimension = dimension des échantillons
*/

Layer::Layer(size_t nbNeurones, size_t inputDataDimension, size_t inputDataSetSize): m_nbNeurones(nbNeurones)
{
    m_W = Matrix(nbNeurones, inputDataDimension,1.0);
    m_Z = Matrix(nbNeurones, inputDataSetSize, 0.0);
    m_A = Matrix(nbNeurones, inputDataSetSize, 0.0);
    m_B = Matrix(nbNeurones, 1, 0.0);
    m_act = nn::Activation::Logistic;

}


// Getters

size_t Layer::getNbNeurones() const
{
    return m_nbNeurones;
}

Matrix &Layer::getW()
{
    return m_W;
}

Matrix &Layer::getB()
{
    return m_B;
}

Matrix &Layer::getZ()
{
    return m_Z;
}

Matrix &Layer::getA()
{
    return m_A;
}

void Layer::computeZ( Matrix& input)
{
    m_Z = m_W * input + m_B;
}

void Layer::computeA( Matrix& input)
{
    computeZ(input);
    m_A = m_Z;
    m_A.apply(nn::Activation::Logistic);
}

// Compute


