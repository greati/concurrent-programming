#include <iostream>
#include <Mat.h>

using Mat::Matrix;

int main(void) {

    for (int i = 4; i < 2048; i = (i << 1)) {
	std::ostringstream a_filename, b_filename;
	a_filename << "Matrizes/A" << i << "x" << i << ".txt";
	b_filename << "Matrizes/B" << i << "x" << i << ".txt";

	Matrix a, b, c;
	Mat::read_matrix(a_filename.str(), a);
	Mat::read_matrix(b_filename.str(), b);
        
        std::map<std::string, double> stats_sequential;
        Mat::perf_mult_with_stats(a, b, c, 20, Mat::sequential_mult, stats_sequential);

        std::map<std::string, double> stats_concurrent;
        Mat::perf_mult_with_stats(a, b, c, 20, Mat::concurrent_mult, stats_concurrent);

        std::cout << "N = " << i << std::endl;

    } 

    return 0;
}
