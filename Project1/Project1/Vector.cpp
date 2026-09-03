#include <iostream>
#include <cmath>
#include "Vector.h"

double& Vector::operator[](int n) {
	return element[n];
}

Vector& Vector::operator=(const Vector& v) {
	if (v.dim == dim && this != &v) {
		for (int i = 0; i < dim; i++) {
			element[i] = v.element[i];
		}
	}
	else std::cout << "Different Dimension." << "\n";

	return *this;
}

Vector Vector::operator+(const Vector& v) {
	if (v.dim == dim) {
		Vector w(v.dim);
		for (int i = 0; i < w.dim; i++)
			w.element[i] = element[i] + v.element[i];
		return w;
	}
	else std::cout << "Different Dimension" << "\n";
	return *this;
}

Vector Vector::operator-(const Vector& v) {
	if (v.dim == dim) {
		Vector w(v.dim);
		for (int i = 0; i < w.dim; i++)
			w.element[i] = element[i] - v.element[i];
		return w;
	}
	else std::cout << "Different Dimension" << "\n";
	return *this;
}

Vector Vector::operator*(const double c) const{
	Vector w(dim);
	for (int i = 0; i < dim; i++)
		w.element[i] = element[i] * c;
	return w;
}

Vector operator*(const double c, const Vector& v) {
	return v * c;
}

Vector& Vector::operator+=(const Vector& v) {
	if (dim == v.dim) {
		for (int i = 0; i < dim; i++)element[i] += v.element[i];
	}
	else std::cout << "Different Dimension" << "\n";

	return *this;
}

Vector& Vector::operator-=(const Vector& v) {
	if (dim == v.dim) {
		for (int i = 0; i < dim; i++)element[i] -= v.element[i];
	}
	else std::cout << "Different Dimension" << "\n";

	return *this;
}

Vector& Vector::operator*=(const double c) {
	for (int i = 0; i < dim; i++)
		element[i] *= c;
	return *this;
}
/*
class Vector {
	friend Vector operator*(double c, Vector& v) ... 
*/

double Vector::dot(const Vector& v) const {
	double result = 0.0;
	if (v.dim == dim) {
		for (int i = 0; i < dim; i++)
			result += element[i] * v.element[i];
		return result;
	}
	else std::cout<< "Different Dimension"<<"\n";
	return 999999.9;


}

double Vector::norm() const{
	return sqrt(dot(*this));
}

Vector Vector::normalize() const{
	return (1 / norm()) * (*this);
}

Vector Vector::cross_product(const Vector& v) const{
	if (dim == 3 && v.dim == 3) {
		Vector w(3);
		w[0] = element[1] * v.element[2] - element[2] * v.element[1];
		w[1] = element[2] * v.element[0] - element[0] * v.element[2];
		w[2] = element[0] * v.element[1] - element[1] * v.element[0];
		return w;
	}
	else std::cout << "Different Dimension" << "\n";
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
	os << "(";
	for (int i = 0; i < v.dim; i++) {
		os << v.element[i];
		if (i != v.dim - 1) os << ", ";
	}
	os << ")";
	return os;
}