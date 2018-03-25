#include <iostream>
#include <chrono>
#include "Mat.h"

using Mat::Matrix;

int main(int argc, char const *argv[])
{
	int n; Mat::ExecType method; bool write;
	Mat::read_arguments(argc, argv, n, method, write);

	Matrix a, b;
	Mat::read_matrix(Mat::get_filename("A", n), a);
	Mat::read_matrix(Mat::get_filename("B", n), b);

	Matrix c;
 	auto start = std::chrono::steady_clock::now();
 	if (method == Mat::CONCURRENT)
		Mat::concurrent_mult(a, b, c);
	else
		Mat::sequential_mult(a, b, c);
	auto end = std::chrono::steady_clock::now();

	std::chrono::duration<double, std::milli> time(end-start);
	std::cout << (method == Mat::CONCURRENT ? "concurrent" : "sequential") <<
		" multiplication of matrixes of size " << n << "x" << n <<
		" completed in " << time.count() << "ms" << std::endl;

	if (write) {
		std::ofstream result_file(Mat::get_filename("C", n));
		Mat::print_matrix(c, result_file);
	}

	return EXIT_SUCCESS;
}
