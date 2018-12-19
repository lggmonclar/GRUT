#pragma once
#include "../src/Vector.h"
#include "../src/Matrix.h"
#include <iostream>

using namespace GRUT::Math;

int main() {
	Matrix4 m4;
	m4.translate(1.0f, 1.0f, 1.0f);

	std::cout << m4 << std::endl;
	getchar();
	return 0;
}