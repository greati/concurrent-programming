#include "Mat.h"

using Mat::Matrix;

/* Compute line i of the result matrix. */
void Mat::compute_mult_line(const Matrix& A, const Matrix& B, Matrix& C, const int & i) {
	for (unsigned int k = 0; k < B[0].size(); ++k) {
		int sum = 0;
		for (unsigned int m = 0; m < A[i].size(); ++m) {
			sum += A[i][m]*B[m][k];
		}
		C[i][k] = sum;
	}
}

/* Sequential multiplication */
void Mat::sequential_mult(const Matrix& A, const Matrix& B, Matrix& C) {
	C.resize(A.size());
	for (auto& c : C)
            c.resize(B[0].size());
	for (unsigned int i = 0; i < C.size(); ++i)
            Mat::compute_mult_line(A, B, C, i);
}

/* Concurrent multiplication */
void Mat::concurrent_mult(const Matrix& A, const Matrix& B, Matrix& C) {
	C.resize(A.size());
	for (auto& c : C)
            c.resize(B[0].size());
	std::vector<std::thread> thread_list;
	for (unsigned int i = 0; i < C.size(); ++i)
		thread_list.push_back(std::thread(compute_mult_line, std::ref(A), std::ref(B), std::ref(C), i));
	for (auto& t : thread_list)
		t.join();
}

void Mat::read_matrix(std::string filename, Matrix& matrix)
{
	std::ifstream file (filename);
	if (!file.good())
		throw std::ifstream::failure("failed to read matrix file " + filename);
	
	int n, m;
	file >> n >> m;

	matrix.resize(n);
	for (auto i = 0; i < n; ++i)
		matrix[i].resize(m);
		
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			int val;
			file >> val;
			matrix[i][j] = val;
		}
	}
}

void Mat::print_matrix(const Matrix& matrix, std::ostream& output)
{
	output << matrix.size() << " " << matrix[0].size() << std::endl;
	for (auto i = matrix.begin(); i != matrix.end(); ++i) {
		for (auto j = i->begin(); j != i->end(); ++j) {
			if (j+1 != i->end())
				output << *j << " ";
			else 
				output << *j;
		}
		output << std::endl;
	}
}
