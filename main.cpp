#include <iostream>
#include "Perceptron.hpp"

using namespace std;

int main()
{

Perceptron input1;
Perceptron input2;
Perceptron neuron(0); // neurone avec biais

neuron.addInput(input1,0.3);
neuron.addInput(input2,0.29);

input1.setOutput(1);
input2.setOutput(-1);

neuron.compute();

cout << "neuron.output : " << neuron.getOutput();
}
