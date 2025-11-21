#include "DataSample.hpp"

#include <vector>

using namespace std;

DataSample::DataSample():m_input(0),m_output(0)
{
    //ctor
}


void DataSample::setInput(vector<double>& input)
{
    m_input = input;
}

const vector<double>& DataSample::getInput() const
{
    return m_input;
}

void DataSample::setOutput(double output)
{

}

double DataSample::getOutput() const
{
    return m_output;
}
