#include <iostream>
#include "Network.hpp"

using namespace std;

int main()
{
Network net;

Perceptron input1;
Perceptron input2;
Perceptron neuron(0.8); // neurone avec biais

neuron.addInput(input1,3);
neuron.addInput(input2,-1);

input1.setOutput(3);
input2.setOutput(-2);

cout << "neuron.output : " << neuron.calcInput();
}
