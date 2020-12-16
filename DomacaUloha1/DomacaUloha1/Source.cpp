#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>

bool checkInput(double input) {
	return std::cin.good() && input > 0;
}

int main() {
	std::cout << std::fixed << std::setprecision(4);
	std::cout << "Zadejte rovinny obrazec, jehoz obsah a obvod chcete spocitat: a - ctverec, b - obdelnik, c - kruh" << std::endl;

	char choice;
	double a, b;
	std::cin >> choice;

	switch (choice) {
	case 'a':
		std::cout << "Zadejte stranu ctverce:" << std::endl;
		std::cin >> a;
		if (checkInput(a)) 
		{
			std::cout << "Obsah ctverce je: " << a*a << std::endl; 
			std::cout << "Obvod ctverce je: " << a*4 << std::endl;
		}
		else
		{
			std::cout << "Nespravny vstup." << std::endl;
		}
		break;
	case 'b':
		std::cout << "Zadejte strany obdelniku:" << std::endl;
		std::cin >> a;
		std::cin >> b;
		if (checkInput(a) && checkInput(b))
		{
			std::cout << "Obsah obdelniku je: " << a * b << std::endl;
			std::cout << "Obvod obdelniku je: " << (a + b) * 2 << std::endl;
		}
		else
		{
			std::cout << "Nespravny vstup." << std::endl;
		}
		break;
	case 'c':
		std::cout << "Zadejte polomer kruznice:" << std::endl;
		std::cin >> a;
		if (checkInput(a))
		{
			std::cout << "Obsah kruznice je: " << M_PI * a * a << std::endl;
			std::cout << "Obvod kruznice je: " << M_PI * 2 * a << std::endl;
		}
		else
		{
			std::cout << "Nespravny vstup." << std::endl;
		}
		break;
	default:
		std::cout << "Nespravny vstup." << std::endl;
	}

	return 0;
}