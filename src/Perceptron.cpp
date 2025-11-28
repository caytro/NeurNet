#include "Perceptron.hpp"
#include "DataSample.hpp"
#include "DataSet.hpp"

#include <stdlib.h>
#include <numeric>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <numeric>

using namespace std;

// Constructor



Perceptron::Perceptron(double biais): m_biais(biais)
{}

// Setters

void Perceptron::addInput(Perceptron& input, double weight)
{
    m_dendrites.emplace_back(input, weight);
}

void Perceptron::setLearningRate(double learningRate)
{
    m_learningRate = learningRate;
}

// Getters


vector<Dendrite>& Perceptron::getDendrites()
{
    return m_dendrites;
}

double Perceptron::getLearningRate() const
{
    return m_learningRate;
}

vector<double>& Perceptron::getZ() // S(Wk . Xk) + b  , size  = DataSet.samples.size() = Un par échantillons
{
    return m_z;
}

vector<double>& Perceptron::getA()  // a(Z) ,  size(A) = size(Z)
{
    return m_a;
}

vector<double>& Perceptron::getE()  // A - Y , size(E) = size(A)
{
    return m_e;
}

vector<double>& Perceptron::getGradientW()  // S(ek . Xk) , Somme sur les échantillons, size == m_dendrites.size()
{
    return m_gradient;
}



// Others

double Perceptron::activationFunction(double z) const
{
    return 1/(1 + exp(-z));
}

vector<double> Perceptron::getWVector() const {
    vector<double> w;
    w.reserve(m_dendrites.size());

    for (const auto& d : m_dendrites)
        w.push_back(d.getWeight());   // un poids par dendrite

    return w;
}

void Perceptron::calcZ(const DataSet &dataSet)
{
    assert(dataSet.getDimension() == m_dendrites.size());
    const auto& samples = dataSet.getSamples();
    const auto& w = getWVector();

    vector<double> m_z(samples.size());

    transform(samples.begin(), samples.end(),
                   m_z.begin(),
                   [&](const DataSample& s) {
                       const auto& x = s.getInput();
                       return inner_product(x.begin(), x.end(),
                                                 w.begin(),m_biais);
                   });
}

void Perceptron::calcA()
{
    vector<double> m_a(m_z.size());
    transform(
        m_z.begin(),
        m_z.end(),
        m_a.begin(),
        [this](const auto& z)
        {
            return activationFunction(z);
        }
    );
}



double Perceptron::calcLogLoss(const DataSet& dataSet) const
{
    assert(dataSet.getSamples().size() > 0);
    const vector<DataSample>& samples = dataSet.getSamples();
    double logLoss = transform_reduce(
        samples.begin(),
        samples.end(),
        m_a.begin(),
        0.0,
        plus<double>(),
        [](const DataSample& s, double a)
        {
            a = clamp(a, 1e-15, 1 - 1e-15);
            double y = s.getOutput();
            return y * log(a) + (1 - y) * log(1 - a);
        }
    );
    logLoss *= - 1 / dataSet.getSamples().size();
    return logLoss;

}





vector<double>& Perceptron::getOutput()
{
    return m_a;
}


