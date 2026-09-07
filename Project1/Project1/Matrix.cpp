#include "Matrix.h"
#include <iostream>
constexpr double eps = 1e-10;  //0과 비교할 때 부동소수점 오차로 인한 오류 방지;

double* Matrix:: operator[](const int n) {
	if (n < 0 || n >= row)
		throw std::out_of_range("Out of range");
	return element + col * n;
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (row != m.row || col != m.col)
		throw std::invalid_argument("Each matrices must have the same size.");
	for (int i = 0; i < row * col; i++)
		*(element + i) = *(m.element + i);
	return *this;
}

Matrix Matrix:: operator+(const Matrix& m)const {
	if (row != m.row || col != m.col)
		throw std::invalid_argument("Each matrices must have the same size.");

	Matrix t(row, col);

	for (int i = 0; i < row * col; i++)
		*(t.element + i) = *(element + i) + *(m.element + i);
	return t;
}

Matrix Matrix:: operator-(const Matrix& m)const {
	if (row != m.row || col != m.col)
		throw std::invalid_argument("Each matrices must have the same size.");

	Matrix t(row, col);

	for (int i = 0; i < row * col; i++)
		*(t.element + i) = *(element + i) - *(m.element + i);
	return t;
}

Matrix Matrix:: operator*(const Matrix& m)const {
	if (col != m.row)
		throw std::invalid_argument("Matrix multiplication requires lhs columns to match rhs rows.");

	Matrix t(row, m.col);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < m.col; j++) {
			t[i][j] = 0;
			for (int k = 0; k < col; k++) {
				t[i][j] += *(element + col * i + k) * *(m.element + k * m.col + j);
			}
		}
	}
	return t;
}

Matrix Matrix::operator*(const double c)const {
	Matrix t(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			t[i][j] = c * (*(element + col * i + j));
	}
	return t;
}

Matrix operator*(const double c, const Matrix& m) {
	return m * c;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	if (row != m.row || col != m.col)
		throw std::invalid_argument("Each matrices must have the same size.");

	for (int i = 0; i < row * col; i++)
		*(element + i) += *(m.element + i);
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	if (row != m.row || col != m.col)
		throw std::invalid_argument("Each matrices must have the same size.");

	for (int i = 0; i < row * col; i++)
		*(element + i) -= *(m.element + i);
	return *this;
}

Matrix& Matrix::operator*=(const double c) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			*(element + col * i + j) *= c;
	}
	return *this;
}

Matrix Matrix::transpose()const {
	Matrix t(col, row);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			t[j][i] = *(element + i * col + j);
	}
	return t;
}

Matrix Matrix::inverse()const {
	if (row != col) throw std::invalid_argument("The row and col sizes must match.");
	if (std::abs(det()) < eps) throw std::invalid_argument("Matrix is singular.");

	Matrix t(row, 2 * col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			t[i][j] = *(element + i * col + j);
		}
		for (int j = col; j < 2 * col; j++) {
			if (i == (j % col))
				t[i][j] = 1;
			else t[i][j] = 0;
		}
	}
	t = t.rref();
	
	Matrix inverse_mat(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = col; j < 2 * col; j++) {
			inverse_mat[i][j % col] = t[i][j];
		}
	}

	return inverse_mat;
}

Matrix Matrix::rref()const {
	Matrix t(row, col);
	t = *this;
	int pivot_row = 0, pivot_col = 0;

	for (; pivot_col < col && pivot_row < row; pivot_col++) {
		int flag = -1;
		for (int i = pivot_row; i < row; i++) {
			if (std::abs(t[i][pivot_col]) > eps) {
				flag = i;
				break;
			}
		}

		if (flag == -1) continue;
		t.switch_row(pivot_row, flag);

		for (int j = pivot_row + 1; j < row; j++) {
			double div = t[j][pivot_col] / t[pivot_row][pivot_col];
			for (int k = pivot_col; k < col; k++) {
				t[j][k] -= div * t[pivot_row][k];
				if (std::abs(t[j][k]) < eps) t[j][k] = 0;
			}
		}
		pivot_row++;
	}



	for (int i = pivot_row - 1; i >= 0; i--) { // backward
		bool flag = false;
		int non_zero;
		for (int k = 0; k < col; k++) {
			if (std::abs(t[i][k]) > 0) {
				non_zero = k;
				flag = true;
				break;
			}
		}

		if (!flag) continue;

		for (int j = i - 1; j >= 0; j--) {
			double factor = t[j][non_zero] / t[i][non_zero];

			for (int l = non_zero; l < col; l++) {
				t[j][l] -= t[i][l] * factor;
				if (std::abs(t[j][l]) < eps)t[j][l] = 0;
			}
		}

		double factor = t[i][non_zero];
		for (int l = non_zero; l < col; l++) {
			t[i][l] /= factor;
			if (std::abs(t[i][l]) < eps)t[i][l] = 0;
		}
	}
	return t;
}

Matrix I_Matrix(const int n) {
	Matrix I(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				I[i][j] = 1;
			else I[i][j] = 0;
		}
	}
	return I;
}

double Matrix::trace()const {
	if (row != col) throw std::invalid_argument("The row and col sizes must match.");
	double result = 0;
	for (int i = 0; i < row; i++) {
		result += *(element + i * row + i);
	}
	return result;
}

double Matrix::det()const {
	if (row != col) throw std::invalid_argument("The row and col sizes must match.");

	Matrix t = (*this);

	int pivot_row = 0, pivot_col = 0, swap_count = 0;

	for (; pivot_col < col && pivot_row < row; pivot_col++) {
		int flag = -1;
		for (int i = pivot_row; i < row; i++) {
			if (std::abs(t[i][pivot_col]) > eps) {
				flag = i;
				break;
			}
		}

		if (flag == -1) continue;
		if (flag != pivot_row) {
			t.switch_row(pivot_row, flag);
			swap_count++;
		}

		for (int j = pivot_row + 1; j < row; j++) {
			double div = t[j][pivot_col] / t[pivot_row][pivot_col];
			for (int k = pivot_col; k < col; k++) {
				t[j][k] -= div * t[pivot_row][k];
				if (std::abs(t[j][k]) < eps) t[j][k] = 0;
			}
		}
		pivot_row++;
	}
	

	double result = 1.0;
	for (int i = 0; i < col; i++) 
		result *= t[i][i];

	if (swap_count % 2 == 0) return result;
	else return -result;
}


void Matrix::switch_row(int a, int b) {
	if (a < 0 || b < 0 || a >= row || b <= 0) throw std::out_of_range("Out Of Range.");

	if (a == b)
		return;

	for (int i = 0; i < col; i++) {
		double temp = *(element + a * col + i);
		*(element + a * col + i) = *(element + b * col + i);
		*(element + b * col + i) = temp;
	}
}

