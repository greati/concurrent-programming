#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>

template<typename TField>
Math::Matrix<TField>::Matrix(const unsigned & _m, const unsigned & _n,
    const TField & _initial) : rows{_m}, cols{_n} 
{
    if (_m <= 0 || _n <= 0)
        throw std::logic_error("A matrix must have a positive number of rows and columns.");

    data = new TField[_m*_n];
    for (auto i = 0u; i < _m; ++i) {
        for (auto j = 0u; j < _n; ++j)
            data[i*_n+j] = _initial;
    }
}

template<typename TField>
Math::Matrix<TField>::Matrix(const Matrix<TField> & from) :  
    rows{from.rows}, cols{from.cols} {
    this->data = new TField[from.rows*from.cols]; 

    for (auto i = 0u; i < from.rows; ++i) {
        for (auto j = 0u; j < from.cols; ++j) {
            this->data[i*from.cols+j] = from(i, j);
        }
    }
}

template<typename TField>
Math::Matrix<TField>::~Matrix() {
    if (data != nullptr)
        delete [] this->data;
}

template<typename TField>
TField& Math::Matrix<TField>::operator() (const unsigned& i, const unsigned& j)
{
  if (i >= rows || j >= cols)
    throw std::logic_error("Accessing matrix position out of bounds");
  return data[i*cols+j];
}

template<typename TField>
TField Math::Matrix<TField>::operator() (const unsigned& i, const unsigned& j) const
{
  if (i >= rows || i >= cols)
    throw std::logic_error("Accessing matrix position out of bounds");
  return data[i*cols+j];
}

template<typename TField>
void Math::Matrix<TField>::set(const unsigned & i, const unsigned & j, const TField & value) {
    this(i, j) = value;
}

template<typename TField>
TField Math::Matrix<TField>::at(const unsigned & i, const unsigned & j) const {
    return this(i, j);
}

template<typename TField>
Math::Matrix<TField> Math::Matrix<TField>::operator*(const Matrix<TField> & _rhs) const {
    return (*(this->multiplier))(*this, _rhs);
}

template<typename TField>
void Math::Matrix<TField>::set_multiplier(std::unique_ptr<MatrixMultiplier<TField>> mult) {
    this->multiplier = std::move(mult);
}

template<typename TField>
Math::Matrix<TField> & Math::Matrix<TField>::operator=(Matrix<TField> m) {
    if (m.cols != this->cols || m.rows != this->rows) {
        if (data != nullptr)
            delete [] this->data;
        this->data = new TField[m.rows*m.cols]; 
    }

    for (auto i = 0u; i < m.rows; ++i) {
        for (auto j = 0u; j < m.cols; ++j) {
            this->data[i*m.cols+j] = m(i, j);
        }
    }
    this->cols = m.cols;
    this->rows = m.rows;
    return *(this);
}

template<typename TField>
std::ostream& Math::operator<<(std::ostream& os, const Math::Matrix<TField>& matrix) {
    for (auto i = 0u; i < matrix.rows; ++i) {
        for (auto j = 0u; j < matrix.cols; ++j) {
            os << std::setprecision(6) << matrix(i, j) << " ";
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}

