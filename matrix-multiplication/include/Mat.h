#ifndef __MAT_H__
#define __MAT_H__

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

namespace Mat {
	typedef std::vector<std::vector<int>> Matrix;

	void compute_mult_line(const Matrix& A, const Matrix& B, Matrix& C, const int & i);
	void sequential_mult(const Matrix& A, const Matrix& B, Matrix& C);
	void concurrent_mult(const Matrix& A, const Matrix& B, Matrix& C);

	void read_matrix(std::string filename, Matrix& matrix);
	void print_matrix(const Matrix& matrix, std::ostream& output=std::cout);
}

#endif
