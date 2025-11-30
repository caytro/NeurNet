#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "Perceptron.hpp"
#include "DataSet.hpp"
#include "Graphic.hpp"



using namespace std;

int main()
{

    size_t inputDimension = 2;
    size_t nbSamples = 200;
    DataSet dataset1(inputDimension);

    // Génération d'un dataSet 2 classes centres et radius aléatoires (avant normalisation)

    // Générateur aléatoire
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<double> x(-10.0, 10.0);
    uniform_real_distribution<double> y(-10.0,10.0);
    uniform_real_distribution<double> radius(0,4);

    double xCenter1 = x(gen);
    double xCenter2 = x(gen);
    double yCenter1 = y(gen);
    double yCenter2 = y(gen);
    double radius1 = radius(gen);
    double radius2 = radius(gen);


    dataset1.genereDiscDataset(nbSamples / 2,  xCenter1,  yCenter1, radius1, 1);
    dataset1.genereDiscDataset(nbSamples / 2, xCenter2, yCenter2, radius2, 0);
    dataset1.computeFeatureMinMax();
    dataset1.normalizeFeatureWise();

    Perceptron neuron(0); // neurone avec biais null
    Perceptron input1, input2;
    neuron.addInput(input1, 1);
    neuron.addInput(input2, 1);
    neuron.setLearningRate(0.001);

    Graphic graphic(dataset1, neuron);

    int maxIter = 10000;
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
