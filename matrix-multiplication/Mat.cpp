#include "Mat.h"

using Mat::Matrix;

const int Mat::min_n = 4;
const int Mat::max_n = 2048;

/* Multiplies line i of a nxm matrix by column j of a nxp matrix. **/
void Mat::mult_line_column(const Matrix& A, const Matrix& B, Matrix& C, const int & n, const int & i, const int & j) {
	int sum = 0;
	for (int k = 0; k < n; ++k) 
		sum += A[i][k] * B[k][j];
	C[i][j] = sum;
}

/* Sequential multiplication */
void Mat::sequential_mult(const Matrix& A, const Matrix& B, Matrix& C, const int & m, const int & n, const int & p) {
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < p; ++j)
			Mat::mult_line_column(A, B, C, n, i, j);
}

/* Concurrent multiplication */
void Mat::concurrent_mult(const Matrix& A, const Matrix& B, Matrix& C, const int & m, const int & n, const int & p) {
	std::vector<std::thread> threadList;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < p; ++j) 
			threadList.push_back(std::thread(mult_line_column, std::ref(A), std::ref(B), std::ref(C), n, i, j));
	for (auto& t : threadList)
		t.join();
}

void Mat::read_arguments(const char* n_arg, const char* method_arg, int& n, char& method)
{
	std::istringstream n_stream(n_arg);
	std::istringstream method_stream(method_arg);
	if (!(n_stream >> n) || !(method_stream >> method))
		throw std::invalid_argument("matrix dimension or processing method not valid");

	if ((n & (n-1)) != 0)
		throw std::invalid_argument("matrix dimension "+std::to_string(n)+" not a power of 2");

	if (method != 'S' && method != 'C')
		throw std::invalid_argument(std::string("invalid processing method ")+method);

	if (n < min_n || n > max_n)
		throw std::invalid_argument("missing matrix of size "+std::to_string(n));
}

void Mat::read_matrix(std::string filename, Matrix& matrix)
{
	auto file = std::ifstream(filename);

	// ignore header with matrix dimensions
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

void Mat::print_matrix(const Matrix& matrix)
{
	for (auto i = matrix.begin(); i != matrix.end(); ++i) {
		for (auto j = i->begin(); j != i->end(); ++j) {
			if (j+1 != i->end())
				std::cout << *j << " ";
			else 
				std::cout << *j;
		}
		std::cout << std::endl;
	}
}
