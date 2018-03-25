#include <iostream>
#include <Mat.h>

using Mat::Matrix;

int main(void) {

	int reps = 20;

	for (int i = Mat::min_n; i <=Mat::max_n; i = (i << 1)) {
		Matrix A, B, C;
		Mat::read_matrix(Mat::get_filename("A", i), A);
		Mat::read_matrix(Mat::get_filename("B", i), B);
		
		std::map<std::string, double> stats_sequential;
		Mat::perf_mult_with_stats(A, B, C, reps, Mat::sequential_mult, stats_sequential);

		std::map<std::string, double> stats_concurrent;
		Mat::perf_mult_with_stats(A, B, C, reps, Mat::concurrent_mult, stats_concurrent);

		std::cout << "N = " << i << std::endl;
	} 

	return 0;
}
