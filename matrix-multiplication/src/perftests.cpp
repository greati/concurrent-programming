#include <iostream>
#include <fstream>
#include "MatTestUtils.h"

using Mat::Matrix;
using MatTestUtils::PerfStats;

int main(int argn, char * args[]) {

    if (argn < 2)
        throw std::invalid_argument("missing results file argument");

    const int reps = 1;
    const int init_size = MatTestUtils::min_n;
    const int end_size = 16;
    const int col_width = 15;

    std::ofstream results;
    results.open(args[1], std::ios::app);
    results << std::setw(col_width) << "n" << std::setw(col_width) 
        << "method" << std::setw(col_width) 
        << "avg" << std::setw(col_width) 
        << "max" << std::setw(col_width) 
        << "min" << std::setw(col_width) 
        << "std" << std::endl;

    for (int i = init_size; i <= end_size; i = (i << 1)) {
        std::cout << "Starting for N = " << i << std::endl;
        std::cout << "-- Reading matrices..." << std::endl;

    	Matrix a, b, c;
    	Mat::read_matrix(MatTestUtils::get_filename("A", i), a);
    	Mat::read_matrix(MatTestUtils::get_filename("B", i), b);
        
        std::cout << "-- Multiplying sequential..." << std::endl;
        PerfStats seqStats = MatTestUtils::mult_perf_stats(a, b, c, reps, Mat::sequential_mult);
        std::cout << "-- Multiplying concurrent..." << std::endl;
        PerfStats concStats = MatTestUtils::mult_perf_stats(a, b, c, reps, Mat::concurrent_mult);

        std::cout << "-- Writing to file..." << std::endl;
        results << std::setw(col_width) << std::to_string(i) << std::setw(col_width) 
            << "S" << std::setw(col_width) << seqStats << std::endl;
        results << std::setw(col_width) << std::to_string(i) << std::setw(col_width) 
            << "C" << std::setw(col_width) << concStats << std::endl;

        std::cout << "-- Done." << std::endl;
    }

    results.close();

    return EXIT_SUCCESS;
}
