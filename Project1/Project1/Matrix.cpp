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

	for (int i = 0; i < row - 1; i++) { 
		for (int j = i+1; j < row ; j++) { // 현재 row보다 아래에 있는 row에 대해 연산
			for (int k = 0; k < col; k++) { //해당 row에 있는 모든 성분에 대해 elimination
				double div1 = t[j][0] / t[i][0];
				t[j][k] = t[j][k]  - t[i][k]* div1;
				if (std::abs(t[j][k]) < eps) t[j][k] = 0; //부동소수점 오차 제거; 연산량은 늘어나지만... 일단은
			}

			int non_zero;
			for (int k = 0; k < col; k++) { //pivot을 1로 만들고 나머지 성분 pivot으로 나눠주기
				if (t[j][k] != 0) {
					non_zero = k;
					for (int l = k; l < col; l++) {
						double div = t[j][k];
						t[j][l] /= div;
						if (std::abs(t[j][l]) < eps) t[j][l] = 0; //오차 제거;
					}
					break;
				}
			}
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


