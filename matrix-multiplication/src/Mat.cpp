#include "Mat.h"

using Mat::Matrix;

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
	C.resize(A.size());
	for (auto& c : C)
		c.resize(B[0].size());

	std::vector<std::thread> thread_list;
	for (unsigned int i = 0; i < C.size(); ++i)
		thread_list.push_back(std::thread(compute_mult_line, std::ref(A), std::ref(B), std::ref(C), i));
	for (auto& t : thread_list)
		t.join();
}

void Mat::read_arguments(int argc, char const *argv[], int& n, char& method, bool& write)
{
	if (argc < 3 )
		throw std::invalid_argument("missing arguments");

	std::istringstream n_stream(argv[1]);
	std::istringstream method_stream(argv[2]);
	if (!(n_stream >> n) || !(method_stream >> method))
		throw std::invalid_argument("matrix dimension or processing method not valid");

	if ((n & (n-1)) != 0)
		throw std::invalid_argument("matrix dimension "+std::to_string(n)+" not a power of 2");

	if (method != 'S' && method != 'C')
		throw std::invalid_argument(std::string("invalid processing method ")+method);

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

std::string Mat::get_filename(std::string matrix_name, int n) {
	std::ostringstream filename;
	filename << "Matrizes/" << matrix_name << n << "x" << n << ".txt";
	return filename.str();
}

void Mat::read_matrix(std::string filename, Matrix& matrix)
{
	std::ifstream file (filename);

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

void Mat::print_matrix(const Matrix& matrix, std::ostream& output)
{
	output << matrix.size() << " " << matrix[0].size() << std::endl;
	for (auto i = matrix.begin(); i != matrix.end(); ++i) {
		for (auto j = i->begin(); j != i->end(); ++j) {
			if (j+1 != i->end())
				output << *j << " ";
			else 
				output << *j;
		}
		output << std::endl;
	}
}

void Mat::perf_mult_with_stats(const Matrix& A, const Matrix& B, Matrix& C, 
        const int & nrepeat, std::function<void(const Matrix&, const Matrix&, Matrix&)> multiplier, 
        std::map<std::string, double>& stats) {

    double average = 0.0, maximum = 0.0, minimum = 0.0, std_deviation = 0.0;
    
    for (int i = 1; i <= nrepeat; ++i) {
        auto start = std::chrono::steady_clock::now();
        multiplier(A, B, C); 
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = end - start;
        double elapsed = duration.count();
        average = 1/i * ((i-1)*average + elapsed);
        maximum = std::max(maximum, elapsed);
        minimum = std::max(minimum, elapsed);
        std_deviation = std::sqrt(1/i*(std::pow(std_deviation, 2)*(i-1) + std::pow((elapsed - average),2)));
    }
    
    // Compute standard deviation

    stats["average"] = average;
    stats["maximum"] = maximum;
    stats["minimum"] = minimum;
    stats["std_deviation"] = std_deviation;

}
