#include <iostream>
#include <chrono>
#include "Mat.h"

using Mat::Matrix;

int main(int argc, char const *argv[])
{
	if (argc < 3 )
		throw std::invalid_argument("missing arguments");
	int n; char mode;
	Mat::read_arguments(argv[1], argv[2], n, mode);

	std::ostringstream a_filename, b_filename;
	a_filename << "Matrizes/A" << n << "x" << n << ".txt";
	b_filename << "Matrizes/B" << n << "x" << n << ".txt";

	Matrix a, b;
	Mat::read_matrix(a_filename.str(), a);
	Mat::read_matrix(b_filename.str(), b);

	Matrix C;
 	auto start = std::chrono::steady_clock::now();
	Mat::sequential_mult(a,b,C);
	auto end = std::chrono::steady_clock::now();

	std::chrono::duration<double, std::milli> time(end-start);
	std::cout << time.count() << std::endl;

	Mat::print_matrix(C);

	return EXIT_SUCCESS;
}
