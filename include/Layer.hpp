#pragma once
#include "DataSet.hpp"
#include "Matrix.hpp"
#include "NeurNetDefs.hpp"

class Layer
{

public:

// Constructors

    Layer(size_t nbNeurones, size_t inputDataDimension,
          size_t inputDataSetSize);

// Setters




// Getters

    size_t getNbNeurones() const;
    Matrix& getW() ;
    Matrix& getB() ;
    Matrix& getZ() ;
    Matrix& getA() ;



// Compute

    void computeZ(Matrix &input);
    void computeA(Matrix &input);


private:

    size_t m_nbNeurones;
    Matrix m_W;
    Matrix m_Z;
    Matrix m_A;
    Matrix m_B; // Utile ? Rajouter une entrée à 1 dans le vecteur Input ?
    nn::Activation m_act;
};
