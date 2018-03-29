#ifndef __MATMULT__
#define __MATMULT__

#include "Matrix.h"

namespace Math {

template<typename TField>
class Matrix;

template<typename TField>
class MatrixMultiplier {
    public:
        virtual void multiply(const Matrix<TField>& A, const Matrix<TField>& B, Matrix<TField>&C) = 0;
        virtual ~MatrixMultiplier(){};
};
}
#endif
