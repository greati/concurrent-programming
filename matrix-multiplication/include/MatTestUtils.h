#ifndef __MAT_TEST_UTILS_H__
#define __MAT_TEST_UTILS_H__

#include "Matrix.h"
#include <iomanip>
#include <experimental/filesystem>
#include <functional>
#include <cmath>
#include <fstream>

/**
 * Methods, structures and auxiliar definitions
 * for testing different matrix multiplication approachs.
 *
 * This was specifically designed according to the
 * requirements of the proposed work. It has
 * methods for reading matrices from file in a fixed
 * format and testing them, generating 
 * statistics about the multiplication performance.
 *
 * @author Vitor Greati, Carlos Vieira
 * @date 2018-03-25
 * */
namespace MatTestUtils {

    extern const int min_n;             /*< Dimension of the smaller matrix in the test set.*/
    extern const int max_n;             /*< Dimension of the largest matrix in the test set.*/
	
    /**
     * Types of multipliers.
     *
     * Used when it is necessary to check what multiplication approach 
     * was requested.
     * */
    enum ExecType {
            SEQUENTIAL = 0,             /*< Sequential approach. */
            CONCURRENT = 1              /*< Concurrent approach. */ 
    };


    /**
     * Represent statistical estimators for the running times of the 
     * multiplication approaches.
     * */
    struct PerfStats {
        double average = 0.0;                   /*< Average running time.*/
        double maximum = 0.0;                   /*< Maximum running time.*/ 
        double minimum = 0.0;                   /*< Minium running time. */
        double stdeviation = 0.0;               /*< Standard deviation regarding the running times.*/
        std::vector<double> running_times;      /*< Sequence of running times registered in the test. */

        /**
         * Simple constructor.
         * */
        PerfStats(){};

        /**
         * Constructor taking the statistical estimators.
         *
         * @param _average
         * @param _maximum
         * @param _minimum
         * @param _stdeviation
         * */
        PerfStats(const double & _average, const double & _maximum, 
                const double & _minimum, const double & _stdeviation)
                : average {_average}, maximum {_maximum}, minimum {_minimum}, stdeviation {_stdeviation}
        {};
    };

    /**
     * Writes the performance statistics using a stream.
     *
     * @param os        Ouput stream.
     * @param ps        Performance statistics.
     * */
    std::ostream& operator<<(std::ostream& os, const PerfStats& ps);

    /**
     * Read command line arguments as specified in the 
     * project requirements.
     *
     * @param argc      Number of arguments.
     * @param argv      Arguments.
     * @param n         Matrix size.
     * @param method    Required method.
     * @param write     True if the result matrix must be written in a file.
     * */
    void read_arguments(int argc, char const *argv[], int& n, ExecType& method, bool& write);

    /**
     * Compose the file name of the test matrices
     * as specified in the project description.
     *
     * @param matrix_name       Matrix name (A | B)
     * @param n                 Matrix size. 
     * */
    std::string get_filename(std::string matrix_name, int n);

    /**
     * Read matrix from the a test file, as specified in the
     * project description.
     *
     * @param filename          Filename.
     * */
    Math::Matrix<int> read_matrix(std::string filename);

    /** 
     * Multiplies AxB repeated times, returning
     * statistical results about the sequence of
     * the running times.
     *
     * @param   A               Left mxn matrix.
     * @param   B               Right nxp matrix.
     * @param   C               Resulting nxn matrix.
     * @param   nrepeat         Number of repetitions.
     * */
    PerfStats mult_perf_stats(const Math::Matrix<int>& A, const Math::Matrix<int>& B, 
        Math::Matrix<int>& C, const int & nrepeat);
}

#endif
