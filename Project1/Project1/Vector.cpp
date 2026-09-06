#include <iostream>
#include <cmath>
#include "Vector.h"
constexpr double eps = 1e-10;

double& Vector::operator[](int n) {
	if (n < 0 || n >= dim) throw std::out_of_range("Out of Range");
	return element[n];
}

Vector& Vector::operator=(const Vector& v) {
	if (this == &v) return *this;
	if (v.dim != dim)
		throw std::invalid_argument("Different Dimension: op =");

	for (int i = 0; i < dim; i++) 
		element[i] = v.element[i];
		
	return *this;
}

Vector Vector::operator+(const Vector& v) const{
	if(v.dim!=dim)
		throw std::invalid_argument("Different Dimension: op +");
	
	Vector w(v.dim);
		for (int i = 0; i < w.dim; i++)
			w.element[i] = element[i] + v.element[i];
		return w;
}

Vector Vector::operator-(const Vector& v) const{
	if (v.dim != dim)
		throw std::invalid_argument("Different Dimension: op -");

	Vector w(v.dim);
	for (int i = 0; i < w.dim; i++)
		w.element[i] = element[i] - v.element[i];
	return w;
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
	if (v.dim != dim)
		throw std::invalid_argument("Different Dimension: op +=");

	for (int i = 0; i < dim; i++)element[i] += v.element[i];

	return *this;
}

Vector& Vector::operator-=(const Vector& v) {
	if (v.dim != dim)
		throw std::invalid_argument("Different Dimension: op -=");

	for (int i = 0; i < dim; i++)element[i] -= v.element[i];
	
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
	if (v.dim != dim)
		throw std::invalid_argument("Different Dimension: dot product");

	double result = 0.0;

	for (int i = 0; i < dim; i++)
		result += element[i] * v.element[i];
	return result;
}

double Vector::norm() const{
	return sqrt(dot(*this));
}

Vector Vector::normalize() const{
	double d = norm();
	if (std::abs(d) <eps) throw std::invalid_argument("Cannot normalize zero vec");
	return (1.0 / d) * (*this);
}

Vector Vector::cross_product(const Vector& v) const{
	if (v.dim != 3 || dim != 3)
		throw std::invalid_argument("Different Dimension: cross product");

	Vector w(3);
	w[0] = element[1] * v.element[2] - element[2] * v.element[1];
	w[1] = element[2] * v.element[0] - element[0] * v.element[2];
    w[2] = element[0] * v.element[1] - element[1] * v.element[0];
	return w;
}

void Vector::print_vec() const{
	int i = 0;
	std::cout << "(";
	for (; i < dim-1; i++) {
		std::cout << element[i] << "; ";
	}
	std::cout << element[i] <<")"<< "\n";
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
	os << "(";
	for (int i = 0; i < v.dim; i++) {
		os << v.element[i];
		if (i != v.dim - 1) os << ", ";
	}
	os << ")";
	return os;
} //이건 AI 코드,,, 추후 공부하겠습니다.