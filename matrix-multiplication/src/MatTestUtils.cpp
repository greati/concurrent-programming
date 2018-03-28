#include "MatTestUtils.h"

using Mat::Matrix;
using MatTestUtils::PerfStats;
namespace fs = std::experimental::filesystem;

const int MatTestUtils::min_n = 4;
const int MatTestUtils::max_n = 2048;

void MatTestUtils::read_arguments(int argc, char const *argv[], int& n, ExecType& method, bool& write)
{
	if (argc < 3 )
		throw std::invalid_argument("missing arguments");

	char method_char;
	std::istringstream n_stream(argv[1]);
	std::istringstream method_stream(argv[2]);
	if (!(n_stream >> n) || !(method_stream >> method_char))
		throw std::invalid_argument("matrix dimension or processing method not valid");

	if ((n & (n-1)) != 0)
		throw std::invalid_argument("matrix dimension "+std::to_string(n)+" not a power of 2");

	method_char = toupper(method_char);
	if (method_char == 'S')
		method = SEQUENTIAL;
	else if (method_char == 'C')
		method = CONCURRENT;
	else
		throw std::invalid_argument(std::string("invalid processing method ")+method_char);

	if (n < min_n || n > max_n)
		throw std::invalid_argument("matrix size "+std::to_string(n)+" out of range");

	if (argc > 3) {
		std::istringstream write_stream(argv[3]);
		if (!(write_stream >> write))
			throw std::invalid_argument("'write' argument provided is not valid");
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

PerfStats MatTestUtils::mult_perf_stats(const Matrix& A, const Matrix& B, Matrix& C, 
        const int & nrepeat, std::function<void(const Matrix&, const Matrix&, Matrix&)> multiplier) {

    double average = 0.0, maximum = 0.0, minimum = 100000, sum_variance = 0.0;
    
    PerfStats p;

    for (int i = 1; i <= nrepeat; ++i) {
        auto start = std::chrono::steady_clock::now();
        multiplier(A, B, C); 
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
    return os << std::to_string(ps.average) << std::setw(15)  << std::to_string(ps.maximum) << std::setw(15) <<
        std::to_string(ps.minimum) << std::setw(15) << std::to_string(ps.stdeviation);
}
