#include "Matrix.h"
#include <iostream>
constexpr double eps = 1e-10;  //0과 비교할 때 부동소수점 오차로 인한 오류 방지;

double* Matrix:: operator[](const int n) {
	if (n < 0 || n >= row) 
		throw std::out_of_range("Out of range");
	return element + col * n;
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
	if (col!=m.row)
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
	for(int i=0; i<row; i++){
		for (int j = 0; j < col; j++)
			t[j][i] = *(element + i * col + j);
	}
	return t;
}

Matrix Matrix::inverse()const {

}

Matrix Matrix::rref()const {
	Matrix t(row, col);
	t = *this;
	int pivot_row = 0, pivot_col = 0;
	
	for (; pivot_col < col && pivot_row < row; pivot_col++) {
		int flag = -1;
		for (int i = pivot_row; i < row; i++) {
			if (std::abs(t[i][pivot_col]) >eps) {
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

	for (; pivot_row >= 0; pivot_row--) {
		double div1 = t[pivot_row][pivot_col];
		for (int i = pivot_col; i <= col; i++) {
			t[pivot_row][i] /= div1;
			if (std::abs(t[pivot_row][i]) < eps) t[pivot_row][i] = 0;
		}

		for (int i = pivot_row - 1; i >= 0; i--) {
			double div = t[i][pivot_col] / t[pivot_row][pivot_col];
			for (int j = pivot_col; j <= col; j++) {
				t[i][j] -= div * t[i][j];
				if (std::abs(t[i][j]) < eps) t[i][j] = 0;
			}
			pivot_col--;
		}
	}
	return t;
}

Matrix Matrix::I_Matrix(const int n)const {
	Matrix I(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; i++) {
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
	//after rref;
}

void switch_row(int a, int b) {
	// a==b 그대로 break;
	//다르면 switch
}

