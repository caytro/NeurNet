#include "Matrix.hpp"
#include <iostream>
#include <numeric>

using namespace std;


// Constructors

Matrix::Matrix(size_t nbLig, size_t nbCol):m_nbLig(nbLig), m_nbCol(nbCol)
{
    for(size_t i = 0 ; i < m_nbLig ; ++i)
    {
        vector<double> newLine(nbCol,0);
        m_matrix.push_back(newLine);
    }
}

// Setters

void Matrix::setValue(size_t i, size_t j, double value)
{
    if ( i >= m_nbLig || j >= m_nbCol )
    {
        throw out_of_range("Erreur index out of range");
    }
    m_matrix[i][j] = value;
}
// Getters
size_t Matrix::getNbLig() const
{
    return m_nbLig;
}

size_t Matrix::getNbCol() const
{
    return m_nbCol;
}

vector<double> Matrix::getNthLig(size_t n) const
{
    if (n >= m_nbLig)
    {
        throw invalid_argument("Invalid parameter n");
    }
    return m_matrix[n];
}

vector<double> Matrix::getNthCol(size_t n) const
{
    if (n >= m_nbCol)
    {
        throw invalid_argument("Invalid parameter n");
    }
    vector<double> col(0);
    for(vector<double> lig : m_matrix)
    {
        col.push_back(lig[n]);
    }
    return col;
}


// Compute

Matrix Matrix::MultiplyMatrix(const Matrix& B, bool transposeA, bool transposeB) const
{
    // return matrix this x B
    // transpose1 <=> transpose this
    // 4 cases

    if ( !transposeA && !transposeB )
    {
        if ( m_nbCol != B.getNbLig() )
        {
            throw length_error("Erreur Dimensions incompatibles");
        }
        Matrix product(m_nbLig,B.getNbCol());
        for(size_t n = 0 ; n < m_nbLig ; ++n)
        {
            for(size_t m = 0 ; m < B.getNbCol() ; ++m)
            {
                vector<double> a = this->getNthLig(n);
                vector<double> b = B.getNthCol(m);
                product.m_matrix[n][m] = inner_product(a.begin(), a.end(), b.begin(),0.0);
            }
        }
        return product;
    }
    else if ( !transposeA && transposeB )
    {
        if ( m_nbCol != B.getNbCol() )
        {
            throw length_error("Erreur Dimensions incompatibles");
        }
        Matrix product(m_nbLig,B.getNbLig());
        for(size_t n = 0 ; n < m_nbLig ; ++n)
        {
            for(size_t m = 0 ; m < B.getNbLig() ; ++m)
            {
                vector<double> a = this->getNthLig(n);
                vector<double> b = B.getNthLig(m);
                product.m_matrix[n][m] = inner_product(a.begin(), a.end(), b.begin(),0.0);
            }
        }
        return product;
    }
    else if ( transposeA && !transposeB )
    {
        if ( m_nbLig != B.getNbLig() )
        {
            throw length_error("Erreur Dimensions incompatibles");
        }
        Matrix product(m_nbCol,B.getNbCol());
        for(size_t n = 0 ; n < m_nbCol ; ++n)
        {
            for(size_t m = 0 ; m < B.getNbCol() ; ++m)
            {
                vector<double> a = this->getNthCol(n);
                vector<double> b = B.getNthCol(m);
                product.m_matrix[n][m] = inner_product(a.begin(), a.end(), b.begin(),0.0);
            }
        }
        return product;
    }
    else if ( transposeA && transposeB )
    {
        if ( m_nbLig != B.getNbCol() )
        {
            throw length_error("Erreur Dimensions incompatibles");
        }
        Matrix product(m_nbCol,B.getNbLig());
        for(size_t n = 0 ; n < m_nbCol ; ++n)
        {
            for(size_t m = 0 ; m < B.getNbLig() ; ++m)
            {
                vector<double> a = this->getNthCol(n);
                vector<double> b = B.getNthLig(m);
                product.m_matrix[n][m] = inner_product(a.begin(), a.end(), b.begin(),0.0);
            }
        }
        return product;
    }
    else
    {
        throw logic_error("Erreur ?!");
    }
}

// Display

void Matrix::display() const
{
    for(size_t i = 0 ; i < m_nbLig ; ++i)
    {
        for (size_t j = 0 ; j < m_nbCol ; ++j)
        {
            cout << m_matrix[i][j] << " ; ";
        }
        cout << endl;
    }

}
