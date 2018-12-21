#pragma once
#include "../src/Vector.h"
#include "../src/Matrix.h"
#include <iostream>

using namespace GRUT::Math;

int main() {
	Matrix<4> m4;
	Matrix<4> m4t{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	std::cout << m4 * m4t << std::endl;
	getchar();
	return 0;
}