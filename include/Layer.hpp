#pragma once
#include "DataSet.hpp"
#include "Matrix.hpp"
#include "NeurNetDefs.hpp"

class Layer
{

public:

// Constructors

    Layer(size_t nbNeurones, size_t nbFeatures, nn::Activation act);

// Setters




// Getters

    size_t getNbNeurones() const;
    Matrix& getW() ;
    const Matrix& getW() const;
    Matrix& getB() ;
    const Matrix& getB() const;
    Matrix& getZ() ;
    const Matrix& getZ() const;
    Matrix& getA() ;
    const Matrix& getA() const;



// Compute

    void computeZ(Matrix &input);
    void computeA(Matrix &input);


private:

    size_t m_nbNeurones;
    size_t m_nbFeatures;
    Matrix m_W;
    Matrix m_B; // Utile ? Rajouter une entrée à 1 dans le vecteur Input ?
    Matrix m_Z;
    Matrix m_A;

    nn::Activation m_act;
};
