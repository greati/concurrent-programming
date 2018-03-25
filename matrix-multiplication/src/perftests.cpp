#include <iostream>
#include <fstream>
#include "MatTestUtils.h"

using Mat::Matrix;
using MatTestUtils::PerfStats;

int main(int argn, char * args[]) {

    if (argn < 2)
        throw std::invalid_argument("missing results file argument");

    const int reps = 1;
    const int INIT_SIZE = 4;
    const int END_SIZE = 16;

    std::ofstream results;
    results.open(args[1], std::ios::app);
    results << "n" << " " << "method" << " " << "avg" << " " << "max" << " " << "min" << " " << "std" << std::endl;

    for (int i = INIT_SIZE; i <= END_SIZE; i = (i << 1)) {
        std::cout << "Starting for N = " << i << std::endl;
        std::cout << "-- Reading matrices..." << std::endl;

    	Matrix a, b, c;
    	Mat::read_matrix(MatTestUtils::get_filename("A", i), a);
    	Mat::read_matrix(MatTestUtils::get_filename("B", i), b);
        
        std::cout << "-- Multiplying sequential..." << std::endl;
        PerfStats seqStats = MatTestUtils::mult_perf_stats(a, b, c, reps, Mat::sequential_mult);
        std::cout << "-- Multiplying concurrent..." << std::endl;
        PerfStats concStats = MatTestUtils::mult_perf_stats(a, b, c, reps, Mat::concurrent_mult);

        std::cout << "-- Writing to file..." << i << std::endl;
        results << std::to_string(i) << " S " << seqStats.tostring() << std::endl;
        results << std::to_string(i) << " C " << concStats.tostring() << std::endl;

        std::cout << "-- Done." << std::endl;
    }

    results.close();

    return 0;
}
