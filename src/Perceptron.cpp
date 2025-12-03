#include "Perceptron.hpp"
#include "DataSample.hpp"
#include "DataSet.hpp"
#include "Dendrite.hpp"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <numeric>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <vector>

using namespace std;

/*************************************/
// Constructors
/************************************/

Perceptron::Perceptron(): m_biais(0.0), m_gradientB(0.0),m_learningRate(1.0)
{}

/***************************************/
// Setters
/***************************************/

void Perceptron::addInput(Perceptron& input, double weight)
{
    m_dendrites.emplace_back(input, weight);
}

void Perceptron::setLearningRate(double learningRate)
{
    m_learningRate = learningRate;
}

/******************************************/
// Getters
/*********************************************/

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
    return m_gradientW;
}

double Perceptron::getGradientB() const
{
    return m_gradientB;
}

double Perceptron::getBiais() const
{
    return m_biais;
}

/*****************************************/
// Compute
/*****************************************/

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

void Perceptron::calcZ(const DataSet &dataSet) // inputNeurone
{
    assert(dataSet.getDimension() == m_dendrites.size());
    const auto& samples = dataSet.getSamples();
    const auto& w = getWVector();
    m_z = vector<double>(0);
    m_z.reserve(samples.size());
     for(const DataSample& sample : dataSet.getSamples())
    {
        vector<double> x = sample.getInput();
        m_z.push_back(inner_product(x.begin(),x.end(), w.begin(), m_biais));
    }
}

void Perceptron::calcZ() // hiddenNeurone
{
    assert(m_dendrites.size() > 0);
    size_t nbSamples0 = m_dendrites[0].getSource().getA().size();
    for (const Dendrite& dendrite : m_dendrites)
    {
        if(dendrite.getSource().getA().size() != nbSamples0)
        {
            throw(runtime_error("Error : Tous les neurones sources doivent avoir le même nombre de samples"));
        }
    }
    m_z = vector<double>(nbSamples0,m_biais);
    for(size_t i = 0 ; i < nbSamples0 ; ++i)
    {
        for(const Dendrite& dendrite : m_dendrites)
        {
            m_z[i] += dendrite.getSource().getA()[i] * dendrite.getWeight();
        }
    }
}

void Perceptron::calcA()
{
    m_a=vector<double>(0);
    m_a.assign(m_z.size(),0.0);
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

void Perceptron::compute(const DataSet& dataSet)
{
    calcZ(dataSet);
    calcA();
}

void Perceptron::compute()
{
    calcZ();
    calcA();
}

void Perceptron::calcE(const DataSet& dataSet )
{
    assert(dataSet.getSamples().size() == m_a.size());
    m_e.assign(m_a.size(),0.0);
    auto& samples = dataSet.getSamples();
    transform(
        samples.begin(),
        samples.end(),
        m_a.begin(),
        m_e.begin(),
        [&](auto& s, double a)
        {
            return a - s.getOutput();
        });
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
    logLoss *= - 1.0 / dataSet.getSamples().size();
    return logLoss;
}


void Perceptron::calcGradientW(const DataSet& dataSet)
{
    assert(m_e.size() == dataSet.getSamples().size());
    size_t k = m_dendrites.size();
    size_t n = m_e.size();
    m_gradientW.assign(m_dendrites.size(),0.0);
    const vector<DataSample>& samples = dataSet.getSamples();
    for (size_t i = 0; i < n; ++i)
    {
        const auto& Xi = samples[i].getInput();   // vecteur de taille K
        for (size_t j = 0; j < k; ++j)
        {
            m_gradientW[j] += m_e[i] * Xi[j];
        }
    }
}

void Perceptron::calcGradientB()
{
    m_gradientB = accumulate(m_e.begin(), m_e.end(),0.0);
}

void Perceptron::updateParams()
{
    for(size_t i = 0 ; i < m_dendrites.size() ; ++i)
    {
        m_dendrites[i].setWeight(m_dendrites[i].getWeight() - m_gradientW[i] * m_learningRate);
    }
    m_biais -= m_gradientB * m_learningRate;
}

// Display

void Perceptron::display(int indent, size_t numSample)
{
    string pad(indent,' ');
    cout << pad << "Perceptron" << endl;
    for(Dendrite dendrite : m_dendrites)
    {
        cout << pad << " - w : " << dendrite.getWeight() << endl;
    }
    cout << pad << " - b : " << m_biais << endl;
    cout << pad << " - z : " << m_z[numSample] << endl;
    cout << pad << " - a : " << m_a[numSample] << endl;
}


