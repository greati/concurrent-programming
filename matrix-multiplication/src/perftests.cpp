#include <iostream>
#include <fstream>
#include "MatTestUtils.h"
#include "ConcurrentMatrixMultiplier.h"

using MatTestUtils::PerfStats;

int main(int argn, char * args[]) {

    try {

        if (argn < 2) {
            auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
            error_msg += ": Missing results file argument.";
            throw std::invalid_argument(error_msg);
        }

        const int reps = 20;
        const int init_size = MatTestUtils::min_n;
        const int end_size = MatTestUtils::max_n;
        const int col_width = MatTestUtils::col_width;

        std::ofstream results;
        results.open(args[1], std::ios::app);
        results.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        results << std::setw(col_width) << "n" << std::setw(col_width) 
            << "method" << std::setw(col_width) 
            << "avg" << std::setw(col_width) 
            << "max" << std::setw(col_width) 
            << "min" << std::setw(col_width) 
            << "std" << std::endl;

        for (int i = init_size; i <= end_size; i = (i << 1)) {
            std::cout << "Starting for N = " << i << std::endl;
            std::cout << "-- Reading matrices..." << std::endl;
            Matrix<int> a = MatTestUtils::read_matrix(MatTestUtils::get_filename("A",i));
            Matrix<int> b = MatTestUtils::read_matrix(MatTestUtils::get_filename("B",i));
            Matrix<int> c {a.rows(), b.cols(), 0};
            
            std::cout << "-- Multiplying sequential..." << std::endl;
            PerfStats seqStats = MatTestUtils::mult_perf_stats(a, b, c, reps);

            std::cout << "-- Multiplying concurrent..." << std::endl;
            a.set_multiplier(std::make_unique<ConcurrentMatrixMultiplier<int>>());
            PerfStats concStats = MatTestUtils::mult_perf_stats(a, b, c, reps);

            std::cout << "-- Writing to file..." << std::endl;
            results << std::setw(col_width) << std::to_string(i) << std::setw(col_width) 
                << "S" << seqStats << std::endl;
            results << std::setw(col_width) << std::to_string(i) << std::setw(col_width) 
                << "C" << concStats << std::endl;

            std::cout << "-- Done." << std::endl;
        }

        results.close();
    } catch (const std::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unknown failure" << std::endl;
        return EXIT_FAILURE;
    }   

    return EXIT_SUCCESS;
}
