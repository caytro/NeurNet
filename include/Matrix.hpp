#pragma once
#include <vector>
#include "NeurNetDefs.hpp"


class Matrix
{
public:


    // Constructors
    Matrix(size_t nbLines, size_t nbCols, double value = 0.0);
    Matrix();
    // Setters
    void setElement(size_t line , size_t col, double value);
    void appendCols(const Matrix& cols);
    void appendLines(const Matrix& lines);

    // Getters
    size_t getNbLines() const;
    size_t getNbCols() const;
    std::vector<double>& getNthLig(size_t n) ;
    const std::vector<double>& getNthLig(size_t n) const ;
    std::vector<double> getNthCol(size_t n) const;
    double getElement(size_t lig, size_t col) const;
    std::vector<std::vector<double>>& getMatrix() ;
    const std::vector<std::vector<double>>& getMatrix() const  ;



    // Compute

    Matrix multiply(Matrix &B, bool transposeA = false, bool transposeB = false) ;
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
    size_t m_nbLines;
    size_t m_nbCols;



};

Matrix operator+(Matrix A, const Matrix &B);
Matrix operator*(Matrix A,  Matrix &B);
Matrix operator*(Matrix A, double lambda);
