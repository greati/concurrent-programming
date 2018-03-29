#ifndef __CONCMULT__
#define __CONCMULT__

#include "Matrix.h"
#include "MatrixMultiplier.h"
#include <thread>

namespace Math {

    template<typename TField>
    class ConcurrentMatrixMultiplier : public MatrixMultiplier<TField> {
        public:
            void multiply(const Matrix<TField>& A, const Matrix<TField>& B, Matrix<TField>& C) {
                std::vector<std::thread> thread_list;
                for (int i = 0; i < C.rows; ++i)
                    thread_list.push_back(std::thread(&ConcurrentMatrixMultiplier<TField>::compute_mult_line, 
                                this, std::ref(A), std::ref(B), std::ref(C), i));
                for (auto& t : thread_list)
                    t.join();
            }

            void compute_mult_line(const Matrix<TField>& A, const Matrix<TField>& B, 
                    Matrix<TField>& C, const int& i) {
                for (int k = 0; k < B.cols; ++k) {
                        int sum = 0;
                        for (int m = 0; m < A.cols; ++m) {
                                sum += A[i][m]*B[m][k];
                        }
                        C[i][k] = sum;
                }
            }

    };
};

#endif
