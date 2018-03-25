#include "Mat.h"

using Mat::Matrix;
using Mat::PerfStats;

const int Mat::min_n = 4;
const int Mat::max_n = 2048;

/* Compute line i of the result matrix. */
void Mat::compute_mult_line(const Matrix& A, const Matrix& B, Matrix& C, const int & i) {
	for (unsigned int k = 0; k < B[0].size(); ++k) {
		int sum = 0;
		for (unsigned int m = 0; m < A[i].size(); ++m) {
			sum += A[i][m]*B[m][k];
		}
		C[i][k] = sum;
	}
}

/* Sequential multiplication */
void Mat::sequential_mult(const Matrix& A, const Matrix& B, Matrix& C) {
	C.resize(A.size());
	for (auto& c : C)
            c.resize(B[0].size());
	for (unsigned int i = 0; i < C.size(); ++i)
            Mat::compute_mult_line(A, B, C, i);
}

/* Concurrent multiplication */
void Mat::concurrent_mult(const Matrix& A, const Matrix& B, Matrix& C) {
	std::vector<std::thread> threadList;
	for (unsigned int i = 0; i < C.size(); ++i)
		threadList.push_back(std::thread(compute_mult_line, std::ref(A), std::ref(B), std::ref(C), i));
	for (auto& t : threadList)
		t.join();
}

void Mat::read_arguments(const char* n_arg, const char* method_arg, int& n, char& method)
{
	std::istringstream n_stream(n_arg);
	std::istringstream method_stream(method_arg);
	if (!(n_stream >> n) || !(method_stream >> method))
		throw std::invalid_argument("matrix dimension or processing method not valid");

	if ((n & (n-1)) != 0)
		throw std::invalid_argument("matrix dimension "+std::to_string(n)+" not a power of 2");

	if (method != 'S' && method != 'C')
		throw std::invalid_argument(std::string("invalid processing method ")+method);

	if (n < min_n || n > max_n)
		throw std::invalid_argument("missing matrix of size "+std::to_string(n));
}

void Mat::read_matrix(std::string filename, Matrix& matrix)
{
	std::ifstream file (filename);

	// ignore header with matrix dimensions
	int n, m;
	file >> n >> m;

	matrix.resize(n);
	for (auto i = 0; i < n; ++i)
		matrix[i].resize(m);
		
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			int val;
			file >> val;
			matrix[i][j] = val;
		}
	}
}

void Mat::print_matrix(const Matrix& matrix)
{
	for (auto i = matrix.begin(); i != matrix.end(); ++i) {
		for (auto j = i->begin(); j != i->end(); ++j) {
			if (j+1 != i->end())
				std::cout << *j << " ";
			else 
				std::cout << *j;
		}
		std::cout << std::endl;
	}
}

const PerfStats& Mat::mult_perf_stats(const Matrix& A, const Matrix& B, Matrix& C, 
        const int & nrepeat, std::function<void(const Matrix&, const Matrix&, Matrix&)> multiplier) {

    double average = 0.0, maximum = 0.0, minimum = 0.0, stdeviation = 0.0;
    
    PerfStats * p = new PerfStats;//{average, maximum, minimum, stdeviation};

    for (int i = 1; i <= nrepeat; ++i) {
        auto start = std::chrono::steady_clock::now();
        multiplier(A, B, C); 
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        double elapsed = duration.count();
        p->running_times.push_back(elapsed);
        average = 1/i * ((i-1)*average + elapsed);
        maximum = std::max(maximum, elapsed);
        minimum = std::max(minimum, elapsed);
        stdeviation = std::sqrt(1/i*(std::pow(stdeviation, 2)*(i-1) + std::pow((elapsed - average),2)));
    }

    p->average = average;
    p->maximum = maximum;
    p->minimum = minimum;
    p->stdeviation = stdeviation;
 
    return (*p);
}
