#ifndef _MATRIX_
#define _MATRIX_

#include <iomanip>
#include <memory>
#include <boost/current_function.hpp>
#include "MatrixMultiplier.h"
#include "SequentialMatrixMultiplier.h"

/**
 * Classes and definitions related to mathematical objects
 * and operations.
 * */
namespace Math {

    /**
     * Represents an m x n matrix, with its data and some operations.
     *
     * It is a class which receives, as template argument, 
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

            TField * data;                                              /*< Matrix data. */
            std::unique_ptr<MatrixMultiplier<TField>> multiplier = 
                std::make_unique<SequentialMatrixMultiplier<TField>>(); /*< Multiplication strategy. */

            /**
             * Swap the ownership of all parameters between two matrices.
             *
             * @param matrix    The matrix with which to swap parameters.
             * */
            void swap(Matrix<TField> matrix);

        public:
            
            unsigned int rows;      /*< Number of rows. */
            unsigned int cols;      /*< Number of columns. */

            /**
             * Constructor for an m x n matrix, with an initial value for all elements.
             *
             * @param _m        Number of lines and columns.
             * @param _initial  Fill the matrix with this value.
             * */
            Matrix(const unsigned & _m, const unsigned & _n, const TField & _initial);

            /**
             * Copy constructor.
             *
             * @param _from     Matrix from which to copy.
             * */
            Matrix(const Matrix<TField> & _from);

            /**
             * Destructor for deleting the matrix data.
             *
             * */
            ~Matrix();


            TField& operator() (const unsigned& i, const unsigned& j);

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

    static const unsigned precision = 6;

    /**
     * Allows printing the matrix to a stream.
     *
     * @param os            Output stream.
     * @param matrix        Matrix to be printed.
     * */
    template<typename TField>
    std::ostream& operator<<(std::ostream& os, const Math::Matrix<TField>& matrix);
}

#include "../src/Matrix.inl"
#endif
