#include "Perceptron.hpp"
#include "Dendrite.hpp"

using namespace std;

Perceptron::Perceptron():m_dendrites(),m_value(0), m_biais(0)
{

}

Perceptron::~Perceptron()
{

}

void Perceptron::connectSource(Perceptron *source, double weight)
{
    m_dendrites.push_back(std::make_unique<Dendrite>(source, this, weight));
}
double Perceptron::calcOutput()
{
    return 0;
}

double Perceptron::getVal()
{
    return m_value;
}
void Perceptron::setVal(double value)
{
    m_value = value;
}

void Perceptron::setBiais(double biais)
{
    m_biais = biais;
}

double Perceptron::getBiais()
{
    return m_biais;
}

vector<unique_ptr<Dendrite>> *Perceptron::getDendrites()
{
    return &m_dendrites;
}




