#include <iostream>
#include <cmath>

int main() {
	double a, b, c;
	/*Zadejte parametry:
	Zadejte delky stran trojuhelnika a, b, c:
	9 8.5 7
	Obsah trojuhelnika je 27.9966
	Zadejte delky stran trojuhelnika a, b, c:
	1.1 2.2 3.3
	Nejedna se o platny trojuhelnik.*/

	std::cout << "Zadejte delky stran trojuhelnika a, b, c:" << std::endl;
	std::cin >> a >> b >> c;
	double s = (a + b + c) / 2.;
	double sq = std::sqrt(s * (s - a) * (s - b) * (s - c));
	if (sq > 0 && a > 0 && b > 0 && c > 0) {
		std::cout << "Obsah trojuhelnika je " << sq << std::endl;
	}
	else {
		std::cout << "Nejedna se o platny trojuhelnik." << std::endl;
	}
	return 0;
}