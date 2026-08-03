#include <iostream>
#include <string>

class Matrix {
private:
	bool broke = false;
	int rows, cols;
	int** matrix;
	int* ld;

	Matrix() {
		broke = true;
		rows = -1;
		cols = -1;
		ld = NULL;
		matrix = NULL;
	}

	int countDigits(int n) {
		int count = 0;
		if (n == 0) {
			return 1;
		}
		if (0 > n) {
			count++;
		}
		while (n != 0) {
			n /= 10;
			count++;
		}
		return count;
	}

public:
	Matrix(int row, int col) {
		rows = row;
		cols = col;
		ld = 0;
		matrix = new int* [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new int[cols];
		}
		ld = new int[cols];
		for (int i = 0;i < cols;i++) {
			ld[i] = 0;
		}
	}
	void setCell(int row, int col, int val) {
		matrix[row][col] = val;
	}

	void fill() {
		for (int i = 0;i < rows;i++) {
			for (int j = 0;j < cols;j++) {
				std::cout << "Value at (" << i + 1 << ", " << j + 1 << "): ";
				std::string s;
				std::getline(std::cin, s);
				int ent = std::stoi(s);
				setCell(i, j, ent);
				int c = countDigits(ent);
				if (c > ld[j]) {
					ld[j] = c;
				}
			}
		}
	}

	int getLD(int col) {
		return ld[col];
	}

	void setLD(int col, int dl) {
		ld[col] = dl;
	}

	bool isNull() {
		if (matrix == NULL) {
			return true;
		}
		return false;
	}

	int getCell(int row, int col) {
		return matrix[row][col];
	}

	int getRows() {
		return rows;
	}

	int getCols() {
		return cols;
	}

	void destroyMatrix() {
		for (int i = 0; i < rows; ++i) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	void printMatrix() {
		if (broke) {
			return;
		}

		for (int i = 0;i < rows;i++) {
			if (i == 0) {
				std::cout << static_cast<char>(218);
			} else if (i == rows - 1) {
				std::cout << static_cast<char>(192);
			} else {
				std::cout << "|";
			}
			for (int j = 0;j < cols;j++) {
				for (int s = 0;s < ld[j] - countDigits(matrix[i][j]);s++) {
					std::cout << " ";
				}
				std::cout << matrix[i][j];
				if (j != cols - 1) {
					std::cout << " ";
				}
			}
			if (i == 0) {
				std::cout << static_cast<char>(191);
			} else if (i == rows - 1) {
				std::cout << static_cast<char>(217);
			} else {
				std::cout << "|";
			}
			std::cout << std::endl;
		}
	}

	Matrix multiply(Matrix m2) {
		if (cols != m2.getRows()) {
			std::cout << "Number of columns of the first matrix is not equal to number of rows of the second matrix" << std::endl;
			return Matrix();
		}
		Matrix mult(rows, m2.getCols());

		for (int i = 0;i < rows;i++) {
			for (int j = 0;j < m2.getCols();j++) {
				int val = 0;
				int c = 0;
				int r = 0;
				for (;c < cols;) {
					val += matrix[i][c] * m2.getCell(r, j);
					c++;
					r++;
				}
				mult.setCell(i, j, val);
				int d = countDigits(val);
				if (d > mult.getLD(j)) {
					mult.setLD(j, d);
				}
			}
		}
		return mult;
	}
};