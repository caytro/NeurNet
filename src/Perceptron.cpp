#include "Perceptron.hpp"
#include "DataSample.hpp"
#include "DataSet.hpp"

#include <stdlib.h>
#include <numeric>
#include <cmath>
#include <cassert>
#include <algorithm>

using namespace std;

// Constructor

Perceptron::Perceptron(double biais): m_biais(biais)
{}

// Setters

void Perceptron::addInput(Perceptron& input, double weight) {
    m_dendrites.emplace_back(input, weight);
}

// Getters


const vector<Dendrite>& Perceptron::getDendrites() const
{
    return m_dendrites;
}



// Others

const double Perceptron::calcInput(const DataSample &datasample) const
{
    assert(datasample.getInput().size() == m_dendrites.size());
    vector<double> input = datasample.getInput();
    return inner_product(
        input.begin(),
        input.end(),
        m_dendrites.begin(),
        m_biais,
        plus<double>(),
        [](double in, const Dendrite& d) { return in * d.getWeight(); } );
}



double Perceptron::compute(const DataSample& datasample) const
{
// TODO (sylvain#1#11/26/25): Implémenter une class Layer et une classe Network pour gérer les neurones d'entrée de façon plus fluide

    assert(m_dendrites.size() > 0);
    return activation(calcInput(datasample));
}

double Perceptron::activation(double z) const
{
    return 1/(1 + exp(-z));
}

double Perceptron::calcLogLoss(const DataSet &dataSet) const
{
    assert(dataSet.getSamples().size() > 0);
    const auto& samples = dataSet.getSamples();

    double logLoss = transform_reduce(
        samples.begin(), samples.end(),
        0.0,
        plus<>(),
        [this](const DataSample &dataSample)
        {
            double a = compute(dataSample);  // on récupère directement le résultat
            a = clamp(a, 1e-15, 1.0 - 1e-15);       // éviter log(0)

            double y = dataSample.getOutput();
            return y * log(a) + (1 - y) * log(1 - a);
        }
    );

    return -1 / dataSet.getSamples().size() * logLoss;
}


vector<double> Perceptron::calcGradientW(const DataSet &dataSet) const
{
    assert(m_dendrites.size() == dataSet.getDimension());
    assert(dataSet.getSamples().size() > 0);
    const auto& samples = dataSet.getSamples();

    double delta = transform_reduce(
        samples.begin(), samples.end(),
        0.0,
        plus<>(),
        [this](const DataSample &dataSample)
        {
            double a = compute(dataSample);  // on récupère directement le résultat
            a = clamp(a, 1e-15, 1.0 - 1e-15);       // éviter log(0)

            double y = dataSample.getOutput();
            return a - y;
        }
    );
    vector<double> result(dataSet.getDimension(), 0.0);

    for (const auto& s : samples)
    {
        const vector<double>& v = s.getInput();
        transform(
            result.begin(), result.end(),
            v.begin(),
            result.begin(),
            plus<>());
    }
    double k = delta / dataSet.getDimension();
    // une seule passe pour multiplier
    transform(
        result.begin(), result.end(),
        result.begin(),
        [k](double x){ return x * k; });

    return result;
}

double Perceptron::calcGradientBiais(const DataSet &dataSet) const
{
    assert(m_dendrites.size() == dataSet.getDimension());
    assert(dataSet.getSamples().size() > 0);
    const auto& samples = dataSet.getSamples();

    double delta = transform_reduce(
        samples.begin(), samples.end(),
        0.0,
        plus<>(),
        [this](const DataSample &dataSample)
        {
            double a = compute(dataSample);  // on récupère directement le résultat
            a = clamp(a, 1e-15, 1.0 - 1e-15);       // éviter log(0)

            double y = dataSample.getOutput();
            return a - y;
        }
    );
    return delta / dataSet.getDimension();
}


double Perceptron::getOutput() const {
    return m_output;
}


