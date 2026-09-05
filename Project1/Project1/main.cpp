#include<iostream>
#include "Vector.h"

int main() {
	try {
		Vector v1(3);
		Vector v2(3);
		Vector v3(3);
		Vector w1(4);
		Vector w2(3);

		v1[0] = 1; v1[1] = 1; v1[2] = 1; // (1;1;1)
		v2[0] = 0; v2[1] = 1; v2[2] = 0; //(0;1;0)
		v1.print_vec();
		v2.print_vec();

		// w1 = v1 + v2;  expect: error op =

		v3 = 5*v1; // expect: v3=(5;5;5)
		v3.print_vec();

		w2 = v1.normalize(); //expect: w2=(0.57735; 0.57735; 0.57735)

		v3 = 2 * v1 + v2 * 3; //expect: v3=(2;5;2)
		v3.print_vec();

		v3 = v1.cross_product(v2); //expect : (-1;0;1)
		v3.print_vec();

		std::cout << "norm: " << v1.norm() << ", " << "dot product with v2: " << v1.dot(v2);
		//expect : norm - 1.73... , dot - 1
	 }
	catch (const std::invalid_argument& e) {
		std::cout << "Error: " << e.what() << "\n";
	}
}