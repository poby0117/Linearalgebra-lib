#pragma once
#include <iostream>
class Vector {
	int dim;
	double* element;

public:
	Vector(int n) {
		if (n < 0) throw std::invalid_argument("Vector Dimension must be positive");
		dim = n;
		element = new double[n];
	}
	/*
	Vector(int n):dim(validate dim(n)), element(new double[dim]){}
	validate함수는 n의 범위를 올바른지 확인하는 함수. 
	initialize 순서는 생성자(int n): <- 여기 뒤에 오는 순서가 아닌 private에 선언된 순서.
	*/
	Vector(const Vector& v) :element(new double[v.dim]), dim(v.dim) {
		for (int i = 0; i < dim; i++)
			element[i] = v.element[i];
	}
	friend std::ostream& operator<<(std::ostream& os, const Vector& v);
	
	
	double& operator[](int n); 
	const double& operator[](const int n)const;

	Vector& operator=(const Vector& v);
	Vector operator+(const Vector& v)const;
	Vector operator-(const Vector& v)const;
	Vector operator*(const double c) const;
	Vector& operator+=(const Vector& v);
	Vector& operator-=(const Vector& v);
	Vector& operator*=(const double c);
	

	double dot(const Vector& v)const;
	Vector cross_product(const Vector& v)const;
	double norm()const;
	Vector normalize()const;


	int get_dim() const{ return dim; }

	void print_vec()const;

	~Vector() {
		if (element) {
			delete[]element;
		}
	}
};

Vector operator*(const double c, const Vector& v);

