#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "MultiLayerNetwork.hpp"
#include "Layer.hpp"
#include "DataSet.hpp"
#include "Matrix.hpp"



using namespace std;

int main()
{
    DataSet dataSet(2,1);
    vector<double> X={1.0,2.0};
    Matrix A(3,4);
    for(size_t i = 0; i < A.getNbLines() ; ++i )
        for(size_t j = 0 ; j < A.getNbCols() ; j++ )
            A.setElement(i,j,double((j + 1) + ( i * A.getNbCols())));

    Matrix B(3,4);
    for(size_t i = 0; i < B.getNbLines() ; ++i )
        for(size_t j = 0 ; j < B.getNbCols() ; j++ )
            B.setElement(i,j,double(((j + 1) + ( i * B.getNbCols())) % 2));

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
    for(size_t i = 0; i < A.getNbLines() ; ++i )
        for(size_t j = 0 ; j < A.getNbCols() ; j++ )
            A.setElement(i,j,double((j + 1) + ( i * A.getNbCols())));

    B = Matrix(4,3);
    for(size_t i = 0; i < B.getNbLines() ; ++i )
        for(size_t j = 0 ; j < B.getNbCols() ; j++ )
            B.setElement(i,j,double(((j + 1) + ( i * B.getNbCols())) % 2));


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

}
