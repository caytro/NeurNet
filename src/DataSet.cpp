#include "DataSet.hpp"
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <ranges>
#include <limits>
#include <cassert>

#include "Matrix.hpp"

using namespace std;


// Constructors

DataSet::DataSet():m_inputDimension(0), m_outputDimension(0)
{}

DataSet::DataSet(size_t inputDimension, size_t outputDimension):
    m_inputDimension(inputDimension),m_outputDimension(outputDimension),
    m_mins(0), m_maxs(0)
{

}


// Setters

void DataSet::setInputDimension(size_t inputDimension)
{
    m_inputDimension = inputDimension;
}

void DataSet::setOutputDimension(size_t outputDimension)
{
    m_outputDimension = outputDimension;
}

void DataSet::addSample(const Matrix& sampleInput, const Matrix& sampleOutput)
{
    if((sampleInput.getNbLig() != m_inputDimension) || (sampleOutput.getNbLig() != m_outputDimension))
        throw("Error : Sample and dataSet should have same dimension");

    m_input.appendCols(sampleInput);
    m_output.appendCols(sampleOutput);
}


// Getters

size_t DataSet::getInputDimension() const
{
    return m_inputDimension;
}

size_t DataSet::getOutputDimension() const
{
    return m_outputDimension;
}

Matrix &DataSet::getInput()
{
    return m_input;
}

Matrix &DataSet::getOutput()
{
    return m_output;
}



// Other

// genereDiscDataset todo : rewrite with Matrix

// void DataSet::genereDiscDataset(size_t nSamples,
//                                double xc, double yc,
//                                double radius,
//                                double output)
// {
//     // Générateur aléatoire
//     static random_device rd;
//     static mt19937 gen(rd());
//     uniform_real_distribution<double> distAngle(0.0, 2.0 * M_PI);
//     uniform_real_distribution<double> distRadius(0.0, 1.0);

//     for (size_t i = 0; i < nSamples; ++i)
//     {
//         double theta = distAngle(gen);
//         double u = distRadius(gen);

//         // Rayon distribué uniformément
//         double r = radius * sqrt(u);

//         double x = xc + r * cos(theta);
//         double y = yc + r * sin(theta);

//         vector<double> input = { x, y };
//         addSample(input, output);
//     }
// }



// Normalization

void DataSet::computeFeatureMinMax()
{
    if (m_input.getNbCol() == 0) return;

    m_mins.assign(m_inputDimension,  numeric_limits<double>::infinity());
    m_maxs.assign(m_inputDimension, -numeric_limits<double>::infinity());

    for(size_t feature = 0 ; feature < m_inputDimension ; ++feature)
    {
        const vector<double>& row = m_input.getNthLig(feature);
        m_mins[feature] = *min_element(row.begin(), row.end());
        m_maxs[feature] = *max_element(row.begin(), row.end());
    }

}

void DataSet::normalizeFeatureWise() {
    for (size_t i = 0 ; i < m_inputDimension ; ++i)
    {
        vector<double>& feature = m_input.getNthLig(i);
        double denominator = m_maxs[i] - m_mins[i];
        transform(
            feature.begin(),
            feature.end(),
            feature.begin(),
            [&](double currentValue)
            {
                return (denominator == 0.0) ? 0.0 : (currentValue - m_mins[i]) / denominator;
            }
            );
    }
}






