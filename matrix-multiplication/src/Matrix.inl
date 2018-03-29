template<typename TField>
Math::Matrix<TField>::Matrix(const unsigned & _m, const unsigned & _n,
    const TField & _initial) : rows{_m}, cols{_n} 
{
    if (_m == 0 || _n == 0) {
        auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": A matrix must have a positive number of rows and columns.";
        throw std::logic_error(error_msg);
    }

    data = new TField[_m*_n];
    for (auto i = 0u; i < _m; ++i) {
        for (auto j = 0u; j < _n; ++j)
            data[i*_n+j] = _initial;
    }
}

template<typename TField>
Math::Matrix<TField>::Matrix(const Matrix<TField> & _from) :  
    rows{_from.rows}, cols{_from.cols} {
    this->data = new TField[_from.rows*_from.cols]; 

    for (auto i = 0u; i < _from.rows; ++i) {
        for (auto j = 0u; j < _from.cols; ++j) {
            this->data[i*_from.cols+j] = _from(i, j);
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
    if (i >= rows || j >= cols) {
        auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": Accessing matrix position out of bounds.";
        throw std::logic_error(error_msg);
    }
    return data[i*cols+j];
}

template<typename TField>
TField Math::Matrix<TField>::operator() (const unsigned& i, const unsigned& j) const
{
    if (i >= rows || i >= cols) {
        auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": Accessing matrix position out of bounds.";
        throw std::logic_error(error_msg);
    }
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
Math::Matrix<TField> Math::Matrix<TField>::operator*(const Matrix<TField> & rhs) const {
    return (*(this->multiplier))(*this, rhs);
}

template<typename TField>
void Math::Matrix<TField>::set_multiplier(std::unique_ptr<MatrixMultiplier<TField>> mult) {
    this->multiplier = std::move(mult);
}

template<typename TField>
Math::Matrix<TField> & Math::Matrix<TField>::operator=(const Matrix<TField> matrix) {
    auto tmp_matrix(matrix);
    swap(tmp_matrix);
    return *this;
}

template<typename TField>
void Math::Matrix<TField>::swap(Matrix<TField> matrix) {
    std::swap(this->data, matrix.data);
    std::swap(this->multiplier, matrix.multiplier);
    std::swap(this->rows, matrix.rows);
    std::swap(this->cols, matrix.cols);
}

template<typename TField>
std::ostream& Math::operator<<(std::ostream& os, const Math::Matrix<TField>& matrix) {
    for (auto i = 0u; i < matrix.rows; ++i) {
        for (auto j = 0u; j < matrix.cols; ++j) {
            os << std::setprecision(precision) << matrix(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

