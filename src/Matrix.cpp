#include "Matrix.hpp"
#include <iostream>
#include <numeric>
#include <cmath>
#include <algorithm>

#include "NeurNetDefs.hpp"


using namespace std;


// Constructors


Matrix::Matrix(size_t nbLig, size_t nbCol, double value):m_nbLig(nbLig), m_nbCol(nbCol)
{
    for(size_t i = 0 ; i < m_nbLig ; ++i)
    {
        vector<double> newLine(nbCol,value);
        m_matrix.push_back(newLine);
    }
}
Matrix::Matrix():m_nbLig(0), m_nbCol(0)
{

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

void Matrix::appendCols(const Matrix &cols)
{
    if(cols.m_nbLig != m_nbLig)
        throw(invalid_argument("Dimensions invalides"));

    for (size_t i = 0; i < m_nbLig; ++i)
    {
        m_matrix[i].reserve(
            m_matrix[i].size() + cols.m_matrix[i].size()
            );
        copy(
            cols.m_matrix[i].begin(),
            cols.m_matrix[i].end(),
            back_inserter(m_matrix[i])
            );
    }
    m_nbCol += cols.m_nbCol;
}

void Matrix::appendLines(const Matrix &lines)
{
    if (lines.m_nbCol != m_nbCol)
        throw(invalid_argument("Dimensions invalides"));
    m_matrix.reserve(m_matrix.size() + lines.m_matrix.size());
    copy(
        lines.m_matrix.begin(),
        lines.m_matrix.end(),
        back_inserter(m_matrix)
        );
    m_nbLig += lines.m_nbLig;
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

vector<double>& Matrix::getNthLig(size_t n)
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

double Matrix::getElement(size_t lig, size_t col) const
{
    if ((lig < m_nbLig) && (col < m_nbCol))
    {
        return m_matrix[lig][col];
    }
    else
    {
        throw(out_of_range(string(lig + "," + col)));
    }
}

std::vector<std::vector<double> > &Matrix::getMatrix()
{
    return m_matrix;
}



// Compute

Matrix Matrix::multiply( Matrix& B, bool transposeA, bool transposeB)
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




Matrix Matrix::hadamard(const Matrix& B) const
{
    if (( m_nbLig == B.getNbLig()) && (m_nbCol == B.getNbCol()))
    {
        Matrix product(m_nbLig, m_nbCol);
        for(size_t i = 0 ; i < m_nbLig ; ++i)
        {
            for(size_t j = 0 ; j < m_nbCol ; ++j)
            {
                product.setValue(i,j, m_matrix[i][j] * B.getElement(i,j));
            }
        }
        return product;
    }
    else
    {
        throw(logic_error("Matrix dimensions should be equals"));
    }
}

void Matrix::multiply(double coef)
{
    for(size_t i= 0 ; i < m_nbLig ; ++i)
    {
        for(size_t j = 0 ; j < m_nbCol ; ++j)
        {
            setValue(i,j,m_matrix[i][j] * coef);
        }
    }
}

Matrix& Matrix::operator *=(double lambda)
{
    multiply(lambda);
    return(*this);
}


void Matrix::add(const Matrix &B, bool broadcast)
{
    if((m_nbLig == B.getNbLig()) && ((!broadcast && (m_nbCol == B.getNbCol())) || (broadcast && B.getNbCol() == 1)))
    {
        for(size_t i = 0 ; i < m_nbLig ; ++i)
        {
            for(size_t j = 0 ; j < m_nbCol ; ++j){
                m_matrix[i][j] += (broadcast ? B.getElement(i,0) : B.getElement(i,j));
            }
        }
    }
    else
    {
        throw(logic_error("Error matrix should have same nbLig. Matrix should have sams nbCol in not broadcast, else B.nbCol() should be equal 1"));
    }
}

Matrix& Matrix::operator+=(const Matrix &B)
{
    add(B,(B.m_nbCol == 1)); // If B.m_nbCol == 1 then broadcast
    return(*this);
}


void Matrix::apply(nn::Activation act)
{
    auto f = [&](double x)
    {
        switch (act)
        {
            case nn::Activation::Relu:
                return x > 0.0 ? x : 0.0;
            case nn::Activation::Logistic:
                return 1.0 / (1.0 + exp(-x));
            default:
                throw(invalid_argument("Invalid activation function"));
        }
    };

    for_each(m_matrix.begin(), m_matrix.end(),
                  [&](vector<double>& row)
                  {
                      transform(row.begin(), row.end(), row.begin(), f);
                  });
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

// Free

Matrix operator+(Matrix A, const Matrix& B)
{
    A.add(B);
    return A;
}

Matrix operator*(Matrix A,  Matrix& B)
{
    Matrix C = A.multiply(B);
    return C;
}

Matrix operator*(Matrix A, double lambda)
{
    A.multiply(lambda);
    return A;
}
