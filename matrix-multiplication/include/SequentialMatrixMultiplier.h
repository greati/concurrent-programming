#ifndef __SEQMULT__
#define __SEQCMULT__

#include "MatrixMultiplier.h"
#include "Matrix.h"
#include <iostream>

/**
 * Provides a method for multiplying matrices based on the mathematical definition 
 * sequentially (single-thread).
 *
 * @author Vitor Greati, Carlos Vieira
 * @date 2018-03-28
 * */
template<typename TField>
class SequentialMatrixMultiplier : public MatrixMultiplier<TField> {

    public:

        /**
         * Computes the product of two matrices using the algorithm from the mathematical definition,
         * using a single thread.
         *
         * @param A         Left operand.
         * @param B         Right operand.
         * @param prod      Product matrix.
         * */
        void multiply(const Matrix<TField>& A, const Matrix<TField>& B, Matrix<TField>& prod) {
            for (auto i = 0u; i < A.rows(); ++i) {
                for (auto j = 0u; j < B.cols(); ++j) {
                    for (auto k = 0u; k < A.cols(); ++k) {
                        prod(i,j) = prod(i,j) + A(i,k) * B(k,j); 
                    }   
                }
            }
        }
};

#endif
