#ifndef _MATRIX_
#define _MATRIX_

#include <iostream>
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
     * It is, actually, a template class, which receives, as template
     * argument, the field of the vector space to which the represented
     * matrix belongs. This is a simplified matrix class, which
     * presents only the multiplication operation (through an Strategy)
     * and some auxiliar methods, such as matrix assignment and
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
            MatrixMultiplier<TField> * multiplier = 
                new SequentialMatrixMultiplier<TField>{};       /*< Multiplication strategy. */

        public:
            
            int rows;               /*< Number of rows. */
            int cols;               /*< Number of columns. */

            /**
             * Constructor for an m x n matrix, accepting values for diagonal elements and others.
             * 
             * It accepts two values: _diag, which is the value for filling
             * the diagonal; and _others, which fills the other matrix
             * positions.
             *
             * @param _m        Number of lines.
             * @param _n        Number of columns.
             * @param _diag	Initial value for cells in the diagonal.
             * @param _others	Initial value for the other cells.
             * */
            Matrix (const int & _m, const int & _n, const TField & _diag, const TField & _others);

            /**
             * Constructor for an m x n matrix, with an initial elements.
             *
             * @param _m        Number of lines and columns.
             * @param _initial  Fill the matrix with this element.
             * */
            Matrix (const int & _m, const int & _n, const TField & _initial);

            /**
             * Constructor which takes an initializer list.
             *
             * @param l         Initializer list with matrix elements.
             * */
            Matrix(const std::initializer_list<std::initializer_list<TField>> & l);

            /**
             * Constructor for a one dimensional matrix from a native array.
             *
             * @param l         Array with elements of the vector.
             * */
            Matrix(const int & n, const TField * array);

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

            /**
             * Access function: takes the element data[i][j].
             *
             * @param i     Element row.
             * @param j     Element column.
             * */
            const TField & at(const int & i, const int & j) const; 

            /**
             * Set function: set data[i][j] to a value.
             *
             * @param i     Element row.
             * @param j     Element column.
             * @param value New value.
             * */
            void set(const int & i, const int & j, const TField & value);

            /**
             * Operator [] for accessing rows of a matrix. This
             * returns a reference.
             * 
             * Since arrays have [] access defined, 
             * this overload allows using [][] for accessing and
             * modifying matrix elements.
             *
             * @param j		Row index.
             * @return 		Pointer to the first element of the row.
             * */
            TField * & operator[](const int & i);

            /**
             * Operator [] for accessing rows of a matrix; this
             * returns a copy.
             *
             * Since arrays have [] access defined, 
             * this overload allows using [][] for accessing
             * matrix elements.
             *
             * @param j		Row index.
             * @return 		Pointer to the first element of the row.
             * */
            TField * operator[](const int & i) const;

            /**
             * Operator for multiplication of matrices.
             *
             * @param _rhs  The matrix to right-multiply this matrix.
             * */
            Matrix<TField> operator*(const Matrix<TField> & _rhs) const;

            /**
             * Set the strategy for multiplication.
             *
             * @param multiplier The new multiplier.
             * */
            void set_multiplier(MatrixMultiplier<TField> * multiplier);

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
