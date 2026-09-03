#pragma once
#include <iostream>
class Vector {
	double* element;
	int dim;

public:
	Vector(int n):element(new double[n]), dim(n){}
	Vector(const Vector& v) :element(new double[v.dim]), dim(v.dim) {
		for (int i = 0; i < dim; i++)
			element[i] = v.element[i];
	}
	friend std::ostream& operator<<(std::ostream& os, const Vector& v);

	double& operator[](int n);
	
	Vector& operator=(const Vector& v);
	Vector operator+(const Vector& v);
	Vector operator-(const Vector& v);
	Vector operator*(const double c) const;
	Vector& operator+=(const Vector& v);
	Vector& operator-=(const Vector& v);
	Vector& operator*=(const double c);
	

	double dot(const Vector& v)const;
	Vector cross_product(const Vector& v)const;
	double norm()const;
	Vector normalize()const;


	int get_dim() { return dim; }

	~Vector() {
		if (element) {
			delete[]element;
		}
	}
};

Vector operator*(const double c, const Vector& v);

