#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>

template<typename TField>
Math::Matrix<TField>::Matrix(const int & _m, const int & _n, 
		    const TField & _diag, const TField & _others) : 
                    rows {_m}, cols {_n} {

    // Test nullity of number of cols and rows
    if (!_m or !_n) 
        throw std::logic_error("A matrix cannot have zero rows or columns.");

    // Create data and populate it
    data = new TField* [_m];
    for (int i = 0; i < _m; ++i) {
        *(data + i) = new TField[_n];
        for (int j = 0; j < _n; ++j) {
			if (i == j)
				data[i][j] = _diag;
			else
				data[i][j] = _others;
        }
    }
}

template<typename TField>
Math::Matrix<TField>::Matrix(const int & _m, const int & _n,
		const TField & _initial) : Matrix(_m, _n, _initial, _initial) {/* empty */}

template<typename TField>
Math::Matrix<TField>::Matrix(const Matrix<TField> & from) :  
    rows {from.rows}, cols {from.cols} {
    this->data = new TField * [from.rows]; 
    for (int i = 0; i < from.rows; ++i)
        this->data[i] = new TField[from.cols];
    for (int i = 0; i < from.rows; ++i) {
        for (int j = 0; j < from.cols; ++j) {
            this->data[i][j] = from[i][j];
        }
    }
}

template<typename TField>
Math::Matrix<TField>::Matrix(const int & n, const TField * array) : Matrix(n, 1, array[0]) {
	for (int i = 0; i < n; ++i)
		this->data[i][0] = array[i];
}

template<typename TField>
Math::Matrix<TField>::Matrix(const std::initializer_list<std::initializer_list<TField>> & l) : 
    data{nullptr} {
    this->rows = l.size();
    
    if (this->rows == 0)
        throw std::invalid_argument("Zero lines not allowed!");
    else {
        this->cols = l.begin()->size();
        if (this->cols == 0)
            throw std::invalid_argument("Zero columns not allowed!");
        else {
            this->data = new TField * [this->rows]; 
            for (int i = 0; i < this->rows; ++i)
                this->data[i] = new TField[this->cols];
        }
    }

    int i = 0; 
    for (auto r : l) {
       int j = 0;
       if ((int) r.size() != this->cols)
           throw std::logic_error("Some element of the matrix is missing!");
       for (auto e : r) {
           data[i][j] = e;
           ++j;
       }
       ++i;
    } 
}

template<typename TField>
Math::Matrix<TField>::~Matrix() {
    if (data != nullptr) {
        for (int i = 0; i < this->rows; ++i)
            delete [] this->data[i];
        delete [] this->data;
    }
    if (multiplier != nullptr)
        delete multiplier;
}

template<typename TField>
void Math::Matrix<TField>::set(const int & i, const int & j, const TField & value) {
    data[i][j] = value;
}

template<typename TField>
const TField & Math::Matrix<TField>::at(const int & i, const int & j) const {
    return data[i][j];
}

template<typename TField>
TField * & Math::Matrix<TField>::operator[](const int & i) {
    if (i < 0 || i >= rows)
            throw std::logic_error("Accessing position out of bounds.");
    return data[i];
}

template<typename TField>
TField * Math::Matrix<TField>::operator[](const int & i) const {
    if (i < 0 || i >= rows)
            throw std::logic_error("Accessing position out of bounds.");
    return data[i];
}

template<typename TField>
Math::Matrix<TField> Math::Matrix<TField>::operator*(const Matrix<TField> & _rhs) const {
    return (*(this->multiplier))(*this, _rhs);
}

template<typename TField>
void Math::Matrix<TField>::set_multiplier(MatrixMultiplier<TField> * _multiplier) {
    if (this->multiplier != nullptr)
        delete this->multiplier;
    this->multiplier = _multiplier;
}

template<typename TField>
Math::Matrix<TField> & Math::Matrix<TField>::operator=(Matrix<TField> m) {
    if (m.cols != this->cols || m.rows != this->rows) {
		if (data != nullptr) {
			for (int i = 0; i < this->rows; ++i)
				delete [] this->data[i];
			delete [] this->data;
		}
        this->data = new TField * [m.rows]; 
        for (int i = 0; i < m.rows; ++i)
            this->data[i] = new TField[m.cols];
    }
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            this->data[i][j] = m[i][j];
        }
    }
    this->cols = m.cols;
    this->rows = m.rows;
    return *(this);
}

template<typename TField>
std::ostream& Math::operator<<(std::ostream& os, const Math::Matrix<TField>& matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            os << std::setprecision(6) << matrix[i][j] << " ";
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}

