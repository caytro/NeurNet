#include "DataSet.hpp"
#include <vector>

using namespace std;

DataSet::DataSet():m_inputDimension(0), m_samples(0)
{

}

void DataSet::setInputDimension(size_t inputDimension)
{
    m_inputDimension = inputDimension;
}
size_t DataSet::getInputDimension() const
{
    return m_inputDimension;
}
void DataSet::addDataSample(vector<double>& input, double output)
{

}

const vector<DataSample>& DataSet::getDatas() const
{
    return m_samples;
}
