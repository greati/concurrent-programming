#ifndef __MAT_H__
#define __MAT_H__

#include <iostream>
#include <thread>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <map>
#include <functional>
#include <cmath>

namespace Mat {
	
	enum ExecType {
		SEQUENTIAL = 0,
		CONCURRENT = 1  
	};

        struct PerfStats {
            double average = 0.0, maximum = 0.0, minimum = 0.0, stdeviation = 0.0;
            std::vector<double> running_times;
            PerfStats(){};
            PerfStats(const double & _average, const double & _maximum, 
                    const double & _minimum, const double & _stdeviation)
                    : average {_average}, maximum {_maximum}, minimum {_minimum}, stdeviation {_stdeviation}
            {};
            std::string tostring() {
                return std::to_string(average) + " " + std::to_string(maximum) + " " + 
                    std::to_string(minimum) + " " + std::to_string(stdeviation);
            }
        };

	extern const int min_n;
	extern const int max_n;
	typedef std::vector<std::vector<int>> Matrix;

	void compute_mult_line(const Matrix& A, const Matrix& B, Matrix& C, const int & i);
	void sequential_mult(const Matrix& A, const Matrix& B, Matrix& C);
	void concurrent_mult(const Matrix& A, const Matrix& B, Matrix& C);

	void read_arguments(int argc, char const *argv[], int& n, char& method, bool& write);
	std::string get_filename(std::string matrix_name, int n);
	void read_matrix(std::string filename, Matrix& matrix);

	void print_matrix(const Matrix& matrix);

        /* Multiplies AxB n times, recording
         * in a map statistics about the running time.
         *
         * @param   A       Left mxn matrix.
         * @param   B       Right nxp matrix.
         * @param   C       Resulting nxn matrix.
         * @param   nrepeat Number of repetitions.
         * */
        const PerfStats& mult_perf_stats(const Matrix&, const Matrix&, Matrix&, const int &, 
                std::function<void(const Matrix&, const Matrix&, Matrix&)>);

	void print_matrix(const Matrix& matrix, std::ostream& output=std::cout);
}

#endif
