#include <iostream>
#include <chrono>
#include "MatTestUtils.h"

using Mat::Matrix;

int main(int argc, char const *argv[])
{
	int n; MatTestUtils::ExecType method; bool write;
	MatTestUtils::read_arguments(argc, argv, n, method, write);

	Matrix a, b;
	Mat::read_matrix(MatTestUtils::get_filename("A", n), a);
	Mat::read_matrix(MatTestUtils::get_filename("B", n), b);

	Matrix c;
 	auto start = std::chrono::steady_clock::now();
 	if (method == MatTestUtils::CONCURRENT)
		Mat::concurrent_mult(a, b, c);
	else
		Mat::sequential_mult(a, b, c);
	auto end = std::chrono::steady_clock::now();

	std::chrono::duration<double, std::milli> time(end-start);
	std::cout << (method == MatTestUtils::CONCURRENT ? "concurrent" : "sequential") <<
		" multiplication of matrixes of size " << n << "x" << n <<
		" completed in " << time.count() << "ms" << std::endl;

	if (write) {
		std::ofstream result_file(MatTestUtils::get_filename("C", n));
		Mat::print_matrix(c, result_file);
		result_file.close();
	}

	return EXIT_SUCCESS;
}
