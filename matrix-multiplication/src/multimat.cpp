#include <iostream>
#include <chrono>
#include "Mat.h"

using Mat::Matrix;

int main(int argc, char const *argv[])
{
	int n; char method; bool write;
	Mat::read_arguments(argc, argv, n, method, write);

	Matrix A, B;
	Mat::read_matrix(Mat::get_filename("A", n), A);
	Mat::read_matrix(Mat::get_filename("B", n), B);

	Matrix C;
 	auto start = std::chrono::steady_clock::now();
 	if (method == 'C')
		Mat::concurrent_mult(A, B, C);
	else
		Mat::sequential_mult(A, B, C);
	auto end = std::chrono::steady_clock::now();

	std::chrono::duration<double, std::milli> time(end-start);
	std::cout << (method == 'C' ? "concurrent" : "sequential") <<
		" multiplication of matrixes of size " << n << "x" << n <<
		" completed in " << time.count() << "ms" << std::endl;

	if (write) {
		std::ofstream result_file(Mat::get_filename("C", n));
		Mat::print_matrix(C, result_file);
	}

	return EXIT_SUCCESS;
}
