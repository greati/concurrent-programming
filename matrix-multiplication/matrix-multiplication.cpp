#include <iostream>
#include <thread>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;

/* Multiplies line i of a nxm matrix by column j of a nxp matrix. **/
void mult_line_column(const Matrix& A, const Matrix& B, Matrix& C, const int & n, const int & i, const int & j) {
	int sum = 0;
	for (int k = 0; k < n; ++k) 
		sum += A[i][k] * B[k][j];
	C[i][j] = sum;
}

/* Sequential multiplication */
void sequential_mult(const Matrix& A, const Matrix& B, Matrix& C, const int & m, const int & n, const int & p) {
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < p; ++j)
			mult_line_column(A, B, C, n, i, j);
}

/* Concurrent multiplication */
void concurrent_mult(const Matrix& A, const Matrix& B, Matrix& C, const int & m, const int & n, const int & p) {
	std::vector<std::thread> threadList;
	int thread_index = 0;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < p; ++j) 
			threadList.push_back(std::thread(mult_line_column, std::ref(A), std::ref(B), std::ref(C), n, i, j));
	for (auto& t : threadList)
		t.join();
}

int main(void) {
	
	const int & m = 4,n = 4,p = 4; 

	Matrix A (m, std::vector<int>(n,2));	
	Matrix B (n, std::vector<int>(p,2));	
	Matrix C (n, std::vector<int>(n,0));	

	concurrent_mult(A,B,C,m,n,p);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j)
			std::cout << C[i][j] << " ";
		std::cout << std::endl;
	}

	return 0;
}
