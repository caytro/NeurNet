#include "DataSet.hpp"
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <ranges>
#include <limits>
#include <cassert>

using namespace std;


// Constructors

DataSet::DataSet():m_dimension(0), m_samples(0)
{}

DataSet::DataSet(size_t dimension): m_dimension(dimension), m_samples(0), m_mins(0), m_maxs(0)
{}


// Setters

void DataSet::setDimension(size_t dimension)
{
    m_dimension = dimension;
}

// Getters

size_t DataSet::getDimension() const
{
    return m_dimension;
}

const vector<DataSample>& DataSet::getSamples() const
{
    return m_samples;
}


// Other

void DataSet::addSample(vector<double>& input, double output)
{
    assert(input.size() == m_dimension);
    m_samples.emplace_back(input, output);
}

void DataSet::genereDiscDataset(size_t nSamples,
                               double xc, double yc,
                               double radius,
                               double output)
{
    // Générateur aléatoire
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<double> distAngle(0.0, 2.0 * M_PI);
    uniform_real_distribution<double> distRadius(0.0, 1.0);

    for (size_t i = 0; i < nSamples; ++i)
    {
        double theta = distAngle(gen);
        double u = distRadius(gen);

        // Rayon distribué uniformément
        double r = radius * sqrt(u);

        double x = xc + r * cos(theta);
        double y = yc + r * sin(theta);

        vector<double> input = { x, y };
        addSample(input, output);
    }
}



// Normalization

void DataSet::computeFeatureMinMax()
{
    if (m_samples.empty()) return;

    m_mins.assign(m_dimension,  numeric_limits<double>::infinity());
    m_maxs.assign(m_dimension, -numeric_limits<double>::infinity());

    for (const auto& sample : m_samples) {
        const auto& v = sample.getInput();

        // Mise à jour en parallèle des mins et maxs
        ranges::transform(
            v, m_mins, m_mins.begin(),
            [](double val, double current) { return min(val, current); }
        );

        ranges::transform(
            v, m_maxs, m_maxs.begin(),
            [](double val, double current) { return max(val, current); }
        );
    }
}

void DataSet::normalizeFeatureWise() {
    for (auto& s : m_samples)
        normalizeSample(s);
}

void DataSet::normalizeSample(DataSample& s)  {
    auto& input = s.getInput();
    for (size_t i = 0; i < input.size(); ++i) {
        double denom = m_maxs[i] - m_mins[i];
        input[i] = (denom == 0.0) ? 0.0 : (input[i] - m_mins[i]) / denom;
    }
}





