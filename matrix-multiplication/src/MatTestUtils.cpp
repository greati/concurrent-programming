#include "MatTestUtils.h"
#include "Matrix.h"

using MatTestUtils::PerfStats;
namespace fs = std::experimental::filesystem;

const int MatTestUtils::col_width = 15;
const int MatTestUtils::min_n = 4;
const int MatTestUtils::max_n = 2048;

void MatTestUtils::read_arguments(int argc, char const *argv[], int& n, ExecType& method, bool& write)
{
	if (argc < 3 ) {
		auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": Missing arguments. Need matrix dimension and processing method.";
        throw std::invalid_argument(error_msg);
	}

	char method_char;
	std::istringstream n_stream(argv[1]);
	std::istringstream method_stream(argv[2]);
	if (!(n_stream >> n) || !(method_stream >> method_char)) {
		auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": Matrix dimension or processing method not valid.";
        throw std::invalid_argument(error_msg);
	}

	if ((n & (n-1)) != 0) {
		auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": Matrix dimension "+std::to_string(n)+" not a power of 2.";
        throw std::invalid_argument(error_msg);
	}

	method_char = toupper(method_char);
	if (method_char == 'S') {
		method = SEQUENTIAL;
	} else if (method_char == 'C') {
		method = CONCURRENT;
	} else {
		auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": Invalid processing method "+method_char;
        throw std::invalid_argument(error_msg);
	}

	if (n < min_n || n > max_n) {
		auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": Matrix size "+std::to_string(n)+" out of range.";
        throw std::invalid_argument(error_msg);
	}

	if (argc > 3) {
		std::istringstream write_stream(argv[3]);
		if (!(write_stream >> write)) {
			auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
	        error_msg += ": 'write' argument provided is not valid (must be 0 or 1).";
	        throw std::invalid_argument(error_msg);
		}
	} else {
		write = true;
	}
}

std::string MatTestUtils::get_filename(std::string matrix_name, int n) {
	std::ostringstream filename;
	if (fs::exists(fs::path("../Matrizes/")))
		filename << "../";
	filename << "Matrizes/" << matrix_name << n << "x" << n << ".txt";
	return filename.str();
}

PerfStats MatTestUtils::mult_perf_stats(const Math::Matrix<int>& A, const Math::Matrix<int>& B, 
        Math::Matrix<int>& C, const int & nrepeat) {

    double average = 0.0, sum_variance = 0.0;
    double maximum = 0.0, minimum = std::numeric_limits<double>::max();
    
    PerfStats p;

    for (int i = 1; i <= nrepeat; ++i) {
        auto start = std::chrono::steady_clock::now();
        C = A * B;
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        double elapsed = duration.count();
        p.running_times.push_back(elapsed);
        average = 1.0/i * ((i-1)*average + elapsed);
        maximum = std::max(maximum, elapsed);
        minimum = std::min(minimum, elapsed);
    }

    for (auto& i : p.running_times)
        sum_variance += std::pow(i-average,2);

    p.average = average;
    p.maximum = maximum;
    p.minimum = minimum;
    p.stdeviation = std::sqrt(1.0/nrepeat * sum_variance);
 
    return p;
}

std::ostream& MatTestUtils::operator<<(std::ostream& os, const PerfStats& ps) {
    return os << std::setw(col_width) 
    	<< std::to_string(ps.average) << std::setw(col_width)
    	<< std::to_string(ps.maximum) << std::setw(col_width) 
    	<< std::to_string(ps.minimum) << std::setw(col_width) 
    	<< std::to_string(ps.stdeviation);
}

Math::Matrix<int> MatTestUtils::read_matrix(std::string filename)
{
	std::ifstream file (filename);
	if (!file.good()) {
		auto error_msg = std::string(BOOST_CURRENT_FUNCTION);
        error_msg += ": Failed to read matrix file " + filename;
        throw std::ifstream::failure(error_msg);
	}
	
	unsigned n, m;
	file >> n >> m;

    Math::Matrix<int> matrix {n, m, 0};

	for (auto i = 0u; i < n; ++i) {
		for (auto j = 0u; j < m; ++j) {
			int val;
			file >> val;
			matrix(i, j) = val;
		}
	}

        return matrix;
}
