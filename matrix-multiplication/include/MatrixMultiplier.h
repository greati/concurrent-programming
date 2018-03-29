#ifndef __MATMULT__
#define __MATMULT__

#include "Matrix.h"

namespace Math {

    // Forward declaration, for dealing with circular dependency.
    template<typename TField>
    class Matrix;

    /**
     * Represents an strategy for matrix multiplication.
     *
     * Implements the function operator which, when called,
     * checks if matrices are compatible for multiplication,
     * and calls an abstract method, which represents
     * the actual multiplication strategy when
     * implemented by concrete subclasses.
     *
     * @author Vitor Greati, Carlos Vieira
     * @date 2018-03-29
     * */
    template<typename TField>
    class MatrixMultiplier {
        public:

            /**
             * Called when one wants to multiply two matrices.
             *
             * First, perform all checks for the multiplication
             * feasibility given the matrices, then
             * calls a method for multiplication.
             *
             * @param A         Left operator.
             * @param B         Right operator.
             * */
            Matrix<TField> operator()(const Matrix<TField>& A, const Matrix<TField>& B){

                // Check multiplication condition
                if (A.cols != B.rows) 
                    throw std::logic_error("You must provide matrices mxn and nxp.");

                Matrix<TField> C {A.rows, B.cols, 0};

                multiply(A,B,C);

                return C;
            }

            /**
             * Empty destructor.
             *
             * Allows destructing concrete classes.
             * */
            virtual ~MatrixMultiplier(){};

        private:

            /**
             * Represents the multiplication strategy.
             *
             * Must be implemented by the concrete subclasses in order to provide
             * a way to multiply matrices.
             *
             * @param A         Left operand.
             * @param B         Right operand.
             * @param C         Product matrix.
             * */
            virtual void multiply(const Matrix<TField>& A, const Matrix<TField>& B, Matrix<TField>&C) = 0;
    };
}
#endif
