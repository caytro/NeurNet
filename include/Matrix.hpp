#pragma once
#include <vector>
#include "NeurNetDefs.hpp"


class Matrix
{
public:


    // Constructors

    Matrix(size_t nbLig, size_t nbCol, double value = 0.0);

    // Setters
    void setValue(size_t i , size_t j, double value);

    // Getters
    size_t getNbLig() const;
    size_t getNbCol() const;
    std::vector<double> getNthLig(size_t n) const;
    std::vector<double> getNthCol(size_t n) const;
    double getElement(size_t lig, size_t col) const;



    // Compute

    Matrix multiply(const Matrix& B, bool transposeA = false, bool transposeB = false) const ;
    void multiply(double lambda) ;
    Matrix& operator*=(double lambda);
    Matrix hadamard(const Matrix& B) const;
    void add(const Matrix& B, bool broadcast = false) ;
    Matrix& operator +=(const Matrix &B);
    void apply(nn::Activation act);

    // Display

    void display() const;


private:
    std::vector<std::vector<double>> m_matrix;   // m_matrix[ligne][colonne]
    size_t m_nbLig;
    size_t m_nbCol;



};

Matrix operator+(Matrix A, const Matrix &B);
Matrix operator*(Matrix A, const Matrix &B);
Matrix operator*(Matrix A, double lambda);
