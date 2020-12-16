#include <iostream>
#include <cmath>

int main() {
	double a, b, c;
	/*Zadejte parametry:
	1 4 -96
	Koren 1: -12
	Koren 2: 8*/

	std::cout << "Zadejte parametry:" << std::endl;
	std::cin >> a >> b >> c;
	float sd = std::sqrt(std::pow(b, 2) - 4 * a * c);
	if (sd >= 0) {
		std::cout << "Koren 1: " << ((-b - sd) / (2 * a)) << std::endl;
		std::cout << "Koren 2: " << ((-b + sd) / (2 * a)) << std::endl;
	}
	else {
		std::cout << "Rovnice nema reseni v R." << std::endl;
	}
	return 0;
}