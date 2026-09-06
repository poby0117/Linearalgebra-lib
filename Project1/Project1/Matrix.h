#pragma once
#include<iostream>

class Matrix {
	int row;
	int col;
	double* element;

public:
	Matrix(int r, int c) {
		if (row <= 0 || col <= 0)
			throw std::invalid_argument("Rows and Cols must be positive.");
		row = r; col = c;
		element = new double[row * col];
	}

	Matrix(const Matrix& M) :row(M.row), col(M.col), element(new double[M.row * M.col]) {
		for (int i = 0; i < M.row * M.col; i++)
			*(element + i) = *(M.element + i);
	}
			
	double* operator[](const int n);

	Matrix operator+(const Matrix& m)const;
	Matrix operator-(const Matrix& m)const;
	Matrix operator*(const Matrix& m)const;
	Matrix operator*(const double c)const;
	Matrix& operator+=(const Matrix& m);
	Matrix& operator-=(const Matrix & m);
	Matrix& operator*=(const double c);

	Matrix transpose()const;
	Matrix inverse()const;
	Matrix rref()const;
	Matrix I_Matrix(const int n)const;

	double det()const;
	double trace()const;
	
	void print_matrix();

	~Matrix() {
		delete[] element;
	}
};

Matrix operator*(const double c, const Matrix& m);