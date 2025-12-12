#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "MultiLayerNetwork.hpp"
#include "Layer.hpp"
#include "Perceptron.hpp"
#include "DataSet.hpp"
#include "Graphic.hpp"
#include "Matrix.hpp"



using namespace std;

int main()
{
    DataSet dataSet(2);
    vector<double> X={1.0,2.0};
    dataSet.addSample(X,1);
    Matrix A(3,4);
    for(size_t i = 0; i < A.getNbLig() ; ++i )
        for(size_t j = 0 ; j < A.getNbCol() ; j++ )
            A.setValue(i,j,double((j + 1) + ( i * A.getNbCol())));

    Matrix B(3,4);
    for(size_t i = 0; i < B.getNbLig() ; ++i )
        for(size_t j = 0 ; j < B.getNbCol() ; j++ )
            B.setValue(i,j,double(((j + 1) + ( i * B.getNbCol())) % 2));

    cout << "A=" << endl;
    A.display();
    cout << "B=" << endl;
    B.display();
    Matrix C = A + B;
    cout << "C=" << endl;
    C.display();
    B += C;
    cout << "B=" << endl;
    B.display();
    Matrix D(3,1,1);
    B += D;
    cout << "B + D =" << endl;
    B.display();
    cout << endl << "Produit" << endl;

    A =  Matrix(3,4);
    for(size_t i = 0; i < A.getNbLig() ; ++i )
        for(size_t j = 0 ; j < A.getNbCol() ; j++ )
            A.setValue(i,j,double((j + 1) + ( i * A.getNbCol())));

    B = Matrix(4,3);
    for(size_t i = 0; i < B.getNbLig() ; ++i )
        for(size_t j = 0 ; j < B.getNbCol() ; j++ )
            B.setValue(i,j,double(((j + 1) + ( i * B.getNbCol())) % 2));


    cout << endl << "A=" << endl;
    A.display();
    cout << endl << "B=" << endl;
    B.display();
    cout << endl << "A2 = A * 2" << endl;
    Matrix A2 = A * 2;
    A2.display();
    cout << endl << "A *=3" << endl;
    A *= 3;
    A.display();

    C = A * B;
    cout << endl << "C=A*B" << endl;
    C.display();

    exit(0);
    // dataSet.computeFeatureMinMax();
    // dataSet.normalizeFeatureWise();
    vector<size_t> nbNeuronesParLayer = {3,3,1};
    MultiLayerNetwork network(nbNeuronesParLayer);
    for(size_t i = 1 ; i < network.getLayers().size() ; ++i)
    {
        network.getNthLayer(i).fullConnect(network.getNthLayer(i-1));
    }
    network.setInputDataSet(dataSet);

    network.getNthLayer(0).getNeurones()[0].getDendrites()[0].setWeight(0.5);



    network.forwardPropagation();
    for(Layer layer : network.getLayers())
    {
        cout << "Layer" << endl;
        for(Perceptron neurone :layer.getNeurones())
        {
            neurone.display(3,0);
        }
    }
}
