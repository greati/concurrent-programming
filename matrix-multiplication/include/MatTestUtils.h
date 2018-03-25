#ifndef __MAT_TEST_UTILS_H__
#define __MAT_TEST_UTILS_H__

#include "Mat.h"
#include <iostream>
#include <thread>
#include <vector>
#include <stdexcept>
#include <experimental/filesystem>
#include <sstream>
#include <fstream>
#include <functional>
#include <cmath>

namespace MatTestUtils {

    extern const int min_n;
    extern const int max_n;
	
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

	void read_arguments(int argc, char const *argv[], int& n, ExecType& method, bool& write);
	std::string get_filename(std::string matrix_name, int n);

    /* Multiplies AxB n times, recording
     * in a map statistics about the running time.
     *
     * @param   A       Left mxn matrix.
     * @param   B       Right nxp matrix.
     * @param   C       Resulting nxn matrix.
     * @param   nrepeat Number of repetitions.
     * */
    PerfStats mult_perf_stats(const Mat::Matrix&, const Mat::Matrix&, Mat::Matrix&, const int &, 
            std::function<void(const Mat::Matrix&, const Mat::Matrix&, Mat::Matrix&)>);
}

#endif
