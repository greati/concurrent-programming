template<typename TField>
Matrix<TField>::Matrix(const unsigned & m, const unsigned & n,
    const TField & initial) : _rows{m}, _cols{n} 
{
    if (m == 0 || n == 0) {
        auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": A matrix must have a positive number of rows and columns.";
        throw std::logic_error(error_msg);
    }

    _data = new TField[m*n];
    for (auto i = 0u; i < m; ++i) {
        for (auto j = 0u; j < n; ++j)
            _data[i*n+j] = initial;
    }
}

template<typename TField>
Matrix<TField>::Matrix(const Matrix<TField> & from) :  
    _rows{from.rows()}, _cols{from.cols()} {
    this->_data = new TField[from.rows()*from.cols()]; 

    for (auto i = 0u; i < from.rows(); ++i) {
        for (auto j = 0u; j < from.cols(); ++j) {
            this->_data[i*from.cols()+j] = from(i, j);
        }
    }
}

template<typename TField>
Matrix<TField>::~Matrix() {
    if (_data != nullptr)
        delete [] this->_data;
}

template<typename TField>
TField& Matrix<TField>::operator() (const unsigned& i, const unsigned& j)
{
    if (i >= this->_rows || j >= this->_cols) {
        auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": Accessing matrix position out of bounds.";
        throw std::logic_error(error_msg);
    }
    return _data[i*this->_cols+j];
}

template<typename TField>
TField Matrix<TField>::operator() (const unsigned& i, const unsigned& j) const
{
    if (i >= this->_rows || i >= this->_cols) {
        auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": Accessing matrix position out of bounds.";
        throw std::logic_error(error_msg);
    }
    return _data[i*this->_cols+j];
}

template<typename TField>
void Matrix<TField>::set(const unsigned & i, const unsigned & j, const TField & value) {
    this(i, j) = value;
}

template<typename TField>
TField Matrix<TField>::at(const unsigned & i, const unsigned & j) const {
    return this(i, j);
}

template<typename TField>
Matrix<TField> Matrix<TField>::operator*(const Matrix<TField> & rhs) const {
    return (*(this->_multiplier))(*this, rhs);
}

template<typename TField>
void Matrix<TField>::set_multiplier(std::unique_ptr<MatrixMultiplier<TField>> mult) {
    if (mult == nullptr) {
        auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": A matrix must have a multiplier.";
        throw std::logic_error(error_msg);
    }
    this->_multiplier = std::move(mult);
}

template<typename TField>
Matrix<TField> & Matrix<TField>::operator=(const Matrix<TField> matrix) {
    auto tmp_matrix(matrix);
    swap(tmp_matrix);
    return *this;
}

template<typename TField>
void Matrix<TField>::swap(Matrix<TField> matrix) {
    std::swap(this->_data, matrix._data);
    std::swap(this->_multiplier, matrix._multiplier);
    std::swap(this->_rows, matrix._rows);
    std::swap(this->_cols, matrix._cols);
}

template<typename TField>
std::ostream& operator<<(std::ostream& os, const Matrix<TField>& matrix) {
    for (auto i = 0u; i < matrix.rows(); ++i) {
        for (auto j = 0u; j < matrix.cols(); ++j) {
            os << std::setprecision(matrix.ostream_precision()) << matrix(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

