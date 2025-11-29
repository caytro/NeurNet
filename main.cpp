#include <iostream>
#include <vector>
#include <algorithm>

#include "Perceptron.hpp"
#include "DataSet.hpp"
#include "Graphic.hpp"


using namespace std;

int main()
{

    size_t inputDimension = 2;
    size_t nbSamples = 200;
    DataSet dataset1(inputDimension);

    dataset1.genereDiscDataset(nbSamples / 2,  -2,  3, 3, 1);
    dataset1.genereDiscDataset(nbSamples / 2, -2, -1, 2, 0);
    dataset1.computeFeatureMinMax();
    dataset1.normalizeFeatureWise();

    Perceptron neuron(0); // neurone avec biais null
    Perceptron input1, input2;
    neuron.addInput(input1, 1);
    neuron.addInput(input2, 1);
    neuron.setLearningRate(0.00001);

    Graphic graphic(dataset1, neuron);

    int maxIter = 200000;
    for(int i=0; i < maxIter ; ++i)
    {
        neuron.calcZ(dataset1);
        neuron.calcA();
        neuron.calcE(dataset1);
        double logLoss = neuron.calcLogLoss(dataset1);
        neuron.calcGradientW(dataset1);
        neuron.calcGradientB();
        neuron.updateParams();
        if ( i % 100 == 0 )
        {
            cout << endl << "*****************" << endl << endl;
            cout << "Itération : " << i << endl;
            cout << "Logloss : " << logLoss << endl;
            graphic.updateDecisionBoundary();
            graphic.render();
        }


    }
    // ------------------------------------------
    // Attendre une touche avant de fermer
    // ------------------------------------------
    sf::Event event;
    while (graphic.isOpen()) {
        while (graphic.getWindow().pollEvent(event)) {

            // Fermeture classique (croix)
            if (event.type == sf::Event::Closed)
                return 0;

            // N'importe quelle touche
            if (event.type == sf::Event::KeyPressed)
                return 0;
        }
    }


}
