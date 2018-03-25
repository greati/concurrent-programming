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


    for (int i = 4; i < 2048; i = (i << 1)) {
        std::cout << "Starting for N = " << i << std::endl;
        std::cout << "-- Reading matrices..." << i << std::endl;

	std::ostringstream a_filename, b_filename;
	a_filename << "Matrizes/A" << i << "x" << i << ".txt";
	b_filename << "Matrizes/B" << i << "x" << i << ".txt";

	Matrix a, b, c;
	Mat::read_matrix(a_filename.str(), a);
	Mat::read_matrix(b_filename.str(), b);
        
        std::cout << "-- Multiplying sequential..." << i << std::endl;
        std::cout << "-- Multiplying concurrent..." << i << std::endl;

        PerfStats seqStats = Mat::mult_perf_stats(a, b, c, 20, Mat::sequential_mult);
        PerfStats concStats = Mat::mult_perf_stats(a, b, c, 20, Mat::concurrent_mult);

        std::cout << "-- Writing to file..." << i << std::endl;
        std::ofstream ofs;
        ofs.open(args[1], std::ios::app);
        ofs << std::to_string(i) << " S " << seqStats.tostring() << std::endl;
        ofs << std::to_string(i) << " C " << concStats.tostring() << std::endl;
        ofs.close();

        std::cout << "-- Done." << std::endl;

    } 

    return 0;
}
