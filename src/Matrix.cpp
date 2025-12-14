#include "Matrix.hpp"
#include <iostream>
#include <numeric>
#include <cmath>
#include <algorithm>

#include "NeurNetDefs.hpp"


using namespace std;


// Constructors


Matrix::Matrix(size_t nbLines, size_t nbCols, double value):
    m_nbLines(nbLines), m_nbCols(nbCols)
{
    for(size_t line = 0 ; line < nbLines ; ++line)
    {
        vector<double> newLine(nbCols,value);
        m_matrix.push_back(newLine);
    }
}
Matrix::Matrix():m_nbLines(0), m_nbCols(0)
{

}
// Setters

void Matrix::setElement(size_t line, size_t col, double value)
{
    if ( line >= m_nbLines || col >= m_nbCols )
    {
        throw out_of_range("Erreur index out of range");
    }
    m_matrix[line][col] = value;
}

void Matrix::appendCols(const Matrix& cols)
{
    if(cols.m_nbLines != m_nbLines)
        throw(invalid_argument("Dimensions invalides"));

    for (size_t line = 0; line < m_nbLines; ++line)
    {
        m_matrix[line].reserve(
            m_matrix[line].size() + cols.m_matrix[line].size()
            );
        copy(
            cols.m_matrix[line].begin(),
            cols.m_matrix[line].end(),
            back_inserter(m_matrix[line])
            );
    }
    m_nbCols += cols.m_nbCols;
}

void Matrix::appendLines(const Matrix &lines)
{
    if (lines.m_nbCols != m_nbCols)
        throw(invalid_argument("Dimensions invalides"));

    m_matrix.reserve(m_matrix.size() + lines.m_matrix.size());
    copy(
        lines.m_matrix.begin(),
        lines.m_matrix.end(),
        back_inserter(m_matrix)
        );
    m_nbLines += lines.m_nbLines;
}





// Getters
size_t Matrix::getNbLines() const
{
    return m_nbLines;
}

size_t Matrix::getNbCols() const
{
    return m_nbCols;
}

vector<double>& Matrix::getNthLig(size_t n)
{
    if (n >= m_nbLines)
    {
        throw invalid_argument("Invalid parameter n");
    }
    return m_matrix[n];
}

const vector<double>& Matrix::getNthLig(size_t n) const
{
    if (n >= m_nbLines)
    {
        throw invalid_argument("Invalid parameter n");
    }
    return m_matrix[n];
}

vector<double> Matrix::getNthCol(size_t n) const
{
    if (n >= m_nbCols)
    {
        throw invalid_argument("Invalid parameter n");
    }
    vector<double> col(0);
    for(vector<double> line : m_matrix)
    {
        col.push_back(line[n]);
    }
    return col;
}

double Matrix::getElement(size_t line, size_t col) const
{
    if ((line < m_nbLines) && (col < m_nbCols))
    {
        return m_matrix[line][col];
    }
    else
    {
        throw(out_of_range(string(line + "," + col)));
    }
}

std::vector<std::vector<double> > &Matrix::getMatrix()
{
    return m_matrix;
}

const std::vector<std::vector<double> > &Matrix::getMatrix() const
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
        if ( m_nbCols != B.getNbLines() )
        {
            throw length_error("Erreur Dimensions incompatibles");
        }
        Matrix product(m_nbLines,B.m_nbCols);
        for(size_t line = 0 ; line < m_nbLines ; ++line)
        {
            for(size_t col = 0 ; col < B.m_nbCols ; ++col)
            {
                vector<double> a = this->getNthLig(line);
                vector<double> b = B.getNthCol(col);
                product.m_matrix[line][col] = inner_product(a.begin(), a.end(), b.begin(),0.0);
            }
        }
        return product;
    }
    else if ( !transposeA && transposeB )
    {
        if ( m_nbCols != B.m_nbCols )
        {
            throw length_error("Erreur Dimensions incompatibles");
        }
        Matrix product(m_nbLines,B.m_nbLines);
        for(size_t line = 0 ; line < m_nbLines ; ++line)
        {
            for(size_t col = 0 ; col < B.m_nbLines ; ++col)
            {
                vector<double> a = this->getNthLig(line);
                vector<double> b = B.getNthLig(col);
                product.m_matrix[line][col] = inner_product(a.begin(), a.end(), b.begin(),0.0);
            }
        }
        return product;
    }
    else if ( transposeA && !transposeB )
    {
        if ( m_nbLines != B.m_nbLines )
        {
            throw length_error("Erreur Dimensions incompatibles");
        }
        Matrix product(m_nbCols,B.m_nbCols);
        for(size_t line = 0 ; line < m_nbCols ; ++line)
        {
            for(size_t col = 0 ; col < B.m_nbCols ; ++col)
            {
                vector<double> a = this->getNthCol(line);
                vector<double> b = B.getNthCol(col);
                product.m_matrix[line][col] = inner_product(a.begin(), a.end(), b.begin(),0.0);
            }
        }
        return product;
    }
    else if ( transposeA && transposeB )
    {
        if ( m_nbLines != B.m_nbCols)
        {
            throw length_error("Erreur Dimensions incompatibles");
        }
        Matrix product(m_nbCols,B.m_nbLines);
        for(size_t line = 0 ; line < m_nbCols ; ++line)
        {
            for(size_t col = 0 ; col < B.m_nbLines ; ++col)
            {
                vector<double> a = this->getNthCol(line);
                vector<double> b = B.getNthLig(col);
                product.m_matrix[line][col] = inner_product(a.begin(), a.end(), b.begin(),0.0);
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
    if (( m_nbLines != B.m_nbLines) || (m_nbCols != B.m_nbCols))
        throw(logic_error("Matrix dimensions should be equals"));

    Matrix product(m_nbLines, m_nbCols);
    for(size_t line = 0 ; line < m_nbLines ; ++line)
    {
        for(size_t col = 0 ; col < m_nbCols ; ++col)
        {
            product.setElement(line,col, m_matrix[line][col] * B.m_matrix[line][col]);
        }
    }
    return product;
}

void Matrix::multiply(double coef)
{
    for(size_t line= 0 ; line < m_nbLines ; ++line)
    {
        for(size_t col = 0 ; col < m_nbCols ; ++col)
        {
            m_matrix[line][col] *= coef;
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
    if((m_nbLines != B.m_nbLines) || (!broadcast && (m_nbCols != B.m_nbCols)) || (broadcast && (B.m_nbCols != 1)))
        throw(logic_error("Error Incoherent dimension and / or broadcast value"));

    for(size_t line = 0 ; line < m_nbLines ; ++line)
    {
        for(size_t col = 0 ; col < m_nbCols ; ++col){
            m_matrix[line][col] += (broadcast ? B.getElement(line,0) : B.getElement(line,col));
        }
    }
}


Matrix& Matrix::operator+=(const Matrix &B)
{
    add(B,(B.m_nbCols == 1)); // If B.m_nbCol == 1 then broadcast
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
    for(size_t line = 0 ; line < m_nbLines ; ++line)
    {
        for (size_t col = 0 ; col < m_nbCols ; ++col)
        {
            cout << m_matrix[line][col] << ((col != (m_nbCols - 1)) ? " : " : "") ;
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
