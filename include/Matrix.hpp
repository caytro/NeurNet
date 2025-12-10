#pragma once
#include <vector>


class Matrix
{
public:


    // Constructors

    Matrix(size_t nbLig, size_t nbCol);

    // Setters
    void setValue(size_t i , size_t j, double value);

    // Getters
    size_t getNbLig() const;
    size_t getNbCol() const;
    std::vector<double> getNthLig(size_t n) const;
    std::vector<double> getNthCol(size_t n) const;



    // Compute

    Matrix MultiplyMatrix(const Matrix& B, bool transposeA = false, bool transposeB = false) const ;

    // Display

    void display() const;

private:
    std::vector<std::vector<double>> m_matrix;   // m_matrix[ligne][colonne]
    size_t m_nbLig;
    size_t m_nbCol;



};
