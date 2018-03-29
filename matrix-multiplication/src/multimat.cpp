#include <iostream>
#include <chrono>
#include "MatTestUtils.h"
#include "Matrix.h"
#include "ConcurrentMatrixMultiplier.h"

int main(int argc, char const *argv[])
{
	try {
		int n; MatTestUtils::ExecType method; bool write;
		MatTestUtils::read_arguments(argc, argv, n, method, write);

	    Math::Matrix<int> A = MatTestUtils::read_matrix(MatTestUtils::get_filename("A",n));
	    Math::Matrix<int> B = MatTestUtils::read_matrix(MatTestUtils::get_filename("B",n));
	    Math::Matrix<int> C {A.rows, B.cols, 0};

	 	if (method == MatTestUtils::CONCURRENT)
	        A.set_multiplier(std::make_unique<Math::ConcurrentMatrixMultiplier<int>>());

	 	auto start = std::chrono::steady_clock::now();
	    C = A*B;
		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double, std::milli> time(end-start);
		std::cout << (method == MatTestUtils::CONCURRENT ? "concurrent" : "sequential") <<
			" multiplication of matrixes of size " << n << "x" << n <<
			" completed in " << time.count() << "ms" << std::endl;

		if (write) {
			auto filename = MatTestUtils::get_filename("C", n);
			std::ofstream result_file(filename);
	        result_file << C.rows << " " << C.cols << std::endl;
	        result_file << C;
			result_file.close();
			std::cout << "output written to " << filename << std::endl;
		}
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unknown failure" << std::endl;
        return EXIT_FAILURE;
    }   

	return EXIT_SUCCESS;
}
