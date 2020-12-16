#ifndef __PROGTEST__ 
#define pause() system("pause"); 
#else
#define pause(); 
#endif

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
	int iterations;
	std::cout << std::fixed << std::setprecision(2);
	std::cin >> iterations;
	if (!std::cin.good() || iterations <= 0) {
		std::cout << "Nespravny vstup." << std::endl;
		return 0;
	}

	double x, y, fi, timedelta, v, fidelta;
	std::cin >> x >> y >> fi >> timedelta >> v >> fidelta;
	if (!std::cin.good()) {
		std::cout << "Nespravny vstup." << std::endl;
		return 0;
	}

	for (; iterations > 0; iterations--) {
		x += v * timedelta * std::cos(fi);
		y += v * timedelta * std::sin(fi);
		fi += timedelta * fidelta;
		fi = std::fmod(fi, M_PI * 2);
		std::cout << "x: " << x << ", y: " << y << ", fi: " << fi << std::endl;
	}

	pause();
	return 0;
}