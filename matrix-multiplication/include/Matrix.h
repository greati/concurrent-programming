#ifndef _MATRIX_
#define _MATRIX_

#include <iomanip>
#include <memory>
#include <boost/current_function.hpp>
#include "MatrixMultiplier.h"
#include "SequentialMatrixMultiplier.h"

/**
 * Represents an m x n matrix, with its data and some operations.
 *
 * It is a template class which takes, as template argument, 
 * the field of the vector space to which the represented
 * matrix belongs. This is a simplified matrix class, which
 * presents only the multiplication operation (through a Strategy)
 * and some auxiliary methods, such as matrix assignment and
 * element access and modification. 
 *
 * @author      Vitor Greati, Carlos Vieira
 * @date        2018-04-29
 * @version     1.0
 * */
template<typename TField>
class Matrix {

    private:

        TField * _data;                                             /*!< Matrix data. */
        std::unique_ptr<MatrixMultiplier<TField>> _multiplier = 
            std::make_unique<SequentialMatrixMultiplier<TField>>(); /*!< Multiplication strategy. */
        unsigned int _ostream_precision = 6;                        /*!< Float precision for string form.*/
        unsigned int _rows;                                         /*!< Number of rows. */
        unsigned int _cols;                                         /*!< Number of columns. */

        /**
         * Swap the ownership of all parameters between two matrices.
         *
         * @param matrix    The matrix with which to swap parameters.
         * */
        void swap(Matrix<TField> matrix);

    public:
        

        /**
         * Constructor for an m x n matrix, with an initial value for all elements.
         *
         * @param m        Number of lines.
         * @param n        Number of columns.
         * @param initial  Fill the matrix with this value.
         * */
        Matrix(const unsigned & m, const unsigned & n, const TField & initial);

        /**
         * Copy constructor.
         *
         * @param from     Matrix from which to copy.
         * */
        Matrix(const Matrix<TField> & from);

        /**
         * Destructor for deleting the matrix data.
         *
         * */
        ~Matrix();

        /**
         * Get the number of rows.
         *
         * @return Number of rows.
         * */
        inline unsigned int rows() const { return this->_rows; }

        /**
         * Get the number of cols.
         *
         * @return Number of cols.
         * */
        inline unsigned int cols() const { return this->_cols; }

        /**
         * Get the precision for printing the matrix entries.
         *
         * @return The precision for ostream printing.
         * */
        inline unsigned int ostream_precision() const { return this->_ostream_precision; }

        /**
         * Get multiplication strategy.
         *
         * @return The multiplication strategy.
         * */
        inline std::unique_ptr<MatrixMultiplier<TField>> multiplier() const { return this->_multiplier; }

        /**
         * Access specific elements by row and column,
         * for assignment.
         *
         * @param i     Element row.
         * @param j     Element column.
         * */
        TField& operator() (const unsigned& i, const unsigned& j);

        /**
         * Access specific elements by row and column,
         * for retrieval.
         *
         * @param i     Element row.
         * @param j     Element column.
         * */
        TField operator() (const unsigned& i, const unsigned& j) const;

        /**
         * Access function: returns the value of row i, column j.
         *
         * @param i     Element row.
         * @param j     Element column.
         * */
        TField at(const unsigned & i, const unsigned & j) const;

        /**
         * Set function: set value of row i, column j.
         *
         * @param i     Element row.
         * @param j     Element column.
         * @param value New value.
         * */
        void set(const unsigned & i, const unsigned & j, const TField & value);

        /**
         * Operator for multiplication of matrices.
         *
         * @param rhs   The matrix to right-multiply this matrix.
         * */
        Matrix<TField> operator*(const Matrix<TField> & rhs) const;

        /**
         * Set the strategy for multiplication.
         *
         * @param mult  The new multiplier.
         * */
        void set_multiplier(std::unique_ptr<MatrixMultiplier<TField>> mult);

        /**
         * Operator for assignment.
         *
         * @param matrix    The current object will be equal to m.
         * */
        Matrix<TField> & operator=(Matrix<TField> matrix);

};

/**
 * Allows printing the matrix to a stream.
 *
 * @param os            Output stream.
 * @param matrix        Matrix to be printed.
 * */
template<typename TField>
std::ostream& operator<<(std::ostream& os, const Matrix<TField>& matrix);

#include "../src/Matrix.inl"
#endif
