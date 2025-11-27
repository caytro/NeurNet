#include <iostream>
#include <vector>
#include <algorithm>

#include "Perceptron.hpp"
#include "DataSet.hpp"
#include "Graphics.hpp"


using namespace std;

int main()
{
    Graphics graphTest;

    size_t inputDimension = 2;
    size_t nbSamples = 50;
    DataSet dataset1(inputDimension);

    dataset1.genereDiscDataset(nbSamples / 2,-2, 2, 1, 1);
    dataset1.genereDiscDataset(nbSamples / 2, 1,3,1,0);
    graphTest.displayDataSet(dataset1);
    for_each(dataset1.getSamples().begin(), dataset1.getSamples().end(), [](const DataSample &ds)
        {
            vector<double> input = ds.getInput();
            cout << "x : " << input.at(0) << "\t";
            cout << "y : " << input.at(1) << "\t";
            cout << "output : " << ds.getOutput() << endl;

        });

    Perceptron neuron(0); // neurone avec biais null
    Perceptron input1, input2;
    neuron.addInput(input1, 12);
    neuron.addInput(input2, -15);

    vector<double> input(2,2);
    DataSample datasample(input, 0);

}
