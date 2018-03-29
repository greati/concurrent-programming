#ifndef __MATMULT__
#define __MATMULT__

#include "Matrix.h"

namespace Math {

    template<typename TField>
    class Matrix;

    template<typename TField>
    class MatrixMultiplier {
        public:

            Matrix<TField> operator()(const Matrix<TField>& A, const Matrix<TField>& B){

                // Check multiplication condition
                if (A.cols != B.rows) 
                    throw std::logic_error("You must provide matrices mxn and nxp.");

                Matrix<TField> C {A.rows, B.cols, 0};
                multiply(A,B,C);
                return C;
            }

            virtual ~MatrixMultiplier(){};

        private:
            virtual void multiply(const Matrix<TField>& A, const Matrix<TField>& B, Matrix<TField>&C) = 0;
    };
}
#endif
