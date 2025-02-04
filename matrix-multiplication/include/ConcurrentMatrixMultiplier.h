#ifndef __CONCMULT__
#define __CONCMULT__

#include "Matrix.h"
#include "MatrixMultiplier.h"
#include <thread>

/**
 * Provides a method for multiplying matrices based on the mathematical definition 
 * using multiple threads.
 *
 * @author Vitor Greati, Carlos Vieira
 * @date 2018-03-28
 * */
template<typename TField>
class ConcurrentMatrixMultiplier : public MatrixMultiplier<TField> {

    public:

        /**
         * Computes the product of two matrices using the algorithm from the mathematical definition,
         * using multiple threads.
         *
         * Allocates one thread for each product row computation.
         * Must be used with caution, since big matrices may surpass
         * some operation system limits when dealing with threads.
         *
         * @param A         Left operand.
         * @param B         Right operand.
         * @param C         Product matrix.
         * */
        void multiply(const Matrix<TField>& A, const Matrix<TField>& B, Matrix<TField>& C) {
            std::vector<std::thread> thread_list;
            for (auto i = 0u; i < C.rows(); ++i)
                thread_list.push_back(std::thread(&ConcurrentMatrixMultiplier<TField>::compute_mult_line, 
                    this, std::ref(A), std::ref(B), std::ref(C), i));
            for (auto& t : thread_list)
                t.join();
        }

        /**
         * Basic operation for computing one row of the product matrix.
         *
         * @param A         Left operand.
         * @param B         Right operand.
         * @param C         Product matrix.
         * @param i         Row index of the product matrix.
         * */
        void compute_mult_line(const Matrix<TField>& A, const Matrix<TField>& B, 
                Matrix<TField>& C, const int& i) {

            for (auto k = 0u; k < B.cols(); ++k) {
                    TField sum = 0;
                    for (auto m = 0u; m < A.cols(); ++m) {
                        sum += A(i, m)*B(m, k);
                    }
                    C(i, k) = sum;
            }
        }
};

#endif
