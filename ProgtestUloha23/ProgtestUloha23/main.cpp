#include <iostream>
#include <cmath>

int main() {
	double ax, ay, bx, by;

	/*Zadejte souradnice bodu A a B:
	2 4
	1 5
	X-ova souradnice stredu S je: 1.5
	Y-ova souradnice stredu S je: 4.5
	Smerovy vektor u ma delku: 1.41421
	Polomer kruznice r ma hodnotu: 0.7071*/

	std::cout << "Zadejte souradnice bodu A a B:" << std::endl;
	std::cin >> ax;
	std::cin >> ay;
	std::cin >> bx;
	std::cin >> by;

	double vec = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));

	std::cout << "X-ova souradnice stredu S je: " << (ax + bx) / 2 << std::endl;
	std::cout << "Y-ova souradnice stredu S je: " << (ay + by) / 2 << std::endl;
	std::cout << "Smerovy vektor u ma delku: " << vec << std::endl;
	std::cout << "Polomer kruznice r ma hodnotu: " << vec / 2 << std::endl;

	return 0;
}