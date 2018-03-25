#include <iostream>
#include <Mat.h>
#include <fstream>

using Mat::Matrix;
using Mat::PerfStats;

int main(int argn, char * args[]) {

    if (argn < 2) {
        std::cout << "Informe o caminho do arquivo de resultados." << std::endl;
        return 1;
    }

    int reps = 20;

    std::ofstream ofs;
    ofs.open(args[1], std::ios::app);
    ofs << "n" << " " << "method" << " " << "avg" << " " << "max" << " " << "min" << " " << "std" << std::endl;

    for (int i = 4; i < 2048; i = (i << 1)) {
        std::cout << "Starting for N = " << i << std::endl;
        std::cout << "-- Reading matrices..." << i << std::endl;

	Matrix a, b, c;
	Mat::read_matrix(Mat::get_filename("A", i), a);
	Mat::read_matrix(Mat::get_filename("B", i), b);
        
        std::cout << "-- Multiplying sequential..." << i << std::endl;
        PerfStats seqStats = Mat::mult_perf_stats(a, b, c, reps, Mat::sequential_mult);
        std::cout << "-- Multiplying concurrent..." << i << std::endl;
        PerfStats concStats = Mat::mult_perf_stats(a, b, c, reps, Mat::concurrent_mult);

        std::cout << "-- Writing to file..." << i << std::endl;
        ofs << std::to_string(i) << " S " << seqStats.tostring() << std::endl;
        ofs << std::to_string(i) << " C " << concStats.tostring() << std::endl;
        ofs.close();

        std::cout << "-- Done." << std::endl;
    }

    return 0;
}
