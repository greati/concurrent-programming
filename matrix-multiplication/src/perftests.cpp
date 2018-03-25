#include <iostream>
#include <fstream>
#include "MatTestUtils.h"

using Mat::Matrix;
using MatTestUtils::PerfStats;

int main(int argn, char * args[]) {

    if (argn < 2)
        throw std::invalid_argument("missing results file argument");

    const int reps = 20;
    const int INIT_SIZE = 4;
    const int END_SIZE = 2048;

    std::ofstream results;
    results.open(args[1], std::ios::app);
    results << std::setw(15) << "n" << std::setw(15) << "method" << std::setw(15) 
        << "avg" << std::setw(15) << "max" 
        << std::setw(15) << "min" << std::setw(15) << "std" << std::endl;

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

        std::cout << "-- Writing to file..." << std::endl;
        results << std::setw(15) << std::to_string(i) << std::setw(15) << "S" 
            << std::setw(15) << seqStats << std::endl;
        results << std::setw(15) << std::to_string(i) << std::setw(15) << "C" 
            << std::setw(15) << concStats << std::endl;

        std::cout << "-- Done." << std::endl;
    }

    results.close();

    return 0;
}
