#ifndef __SEQMULT__
#define __SEQCMULT__

#include "MatrixMultiplier.h"
#include "Matrix.h"
#include <iostream>

namespace Math {
    template<typename TField>
    class SequentialMatrixMultiplier : public MatrixMultiplier<TField> {
        public:
            void multiply(const Matrix<TField>& A, const Matrix<TField>& B, Matrix<TField>& prod) {
                for (int i = 0; i < A.rows; ++i) {
                    for (int j = 0; j < B.cols; ++j) {
                        for (int k = 0; k < A.cols; ++k) {
                            prod[i][j] = prod[i][j] + A[i][k] * B[k][j]; 
                        }   
                    }
                }
            }
    };
};

#endif
