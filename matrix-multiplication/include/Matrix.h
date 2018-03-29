#ifndef _MATRIX_
#define _MATRIX_

#include <iostream>
#include <memory>
#include <functional>
#include <vector>
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

            TField ** data;                                     /*< Matrix data. */
            std::unique_ptr<MatrixMultiplier<TField>> multiplier = 
                std::make_unique<SequentialMatrixMultiplier<TField>>();       /*< Multiplication strategy. */

        public:
            
            unsigned int rows;               /*< Number of rows. */
            unsigned int cols;               /*< Number of columns. */

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
             * */
            Matrix(const Matrix<TField> & from);

            /**
             * Destructor for deleting the matrix data.
             *
             * */
            ~Matrix();


            TField& operator() (const unsigned& i, const unsigned& j);

            TField operator() (const unsigned& i, const unsigned& j) const;

            /**
             * Access function: takes the element data[i][j].
             *
             * @param i     Element row.
             * @param j     Element column.
             * */
            TField at(const unsigned & i, const unsigned & j) const;

            /**
             * Set function: set data[i][j] to a value.
             *
             * @param i     Element row.
             * @param j     Element column.
             * @param value New value.
             * */
            void set(const unsigned & i, const unsigned & j, const TField & value);

            /**
             * Operator for multiplication of matrices.
             *
             * @param _rhs  The matrix to right-multiply this matrix.
             * */
            Matrix<TField> operator*(const Matrix<TField> & _rhs) const;

            /**
             * Set the strategy for multiplication.
             *
             * @param mult The new multiplier.
             * */
            void set_multiplier(std::unique_ptr<MatrixMultiplier<TField>> mult);

            /**
             * Operator for assignment.
             *
             * @param m     The current object will be equal to m.
             * */
            Matrix<TField> & operator=(Matrix<TField> m);

    };

    /**
     * Allows printing the matrix by stream.
     *
     * @param os            Output stream.
     * @param matrix        Matrix to be printed.
     * */
    template<typename TField>
    std::ostream& operator<<(std::ostream& os, const Math::Matrix<TField>& matrix);
}

#include "../src/Matrix.inl"
#endif
