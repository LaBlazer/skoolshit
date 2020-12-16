#ifndef __PROGTEST__ 
#define pause() system("pause"); 
#else
#define pause(); 
#endif

#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	int N;
	std::cin >> N;
	std::cout << std::fixed << std::setprecision(3);
	if (!std::cin.good() || N <= 0) {
		std::cout << "Nespravny vstup." << std::endl;
		return 0;
	}

	double *Va = new double[N], *Vb = new double[N];
	double aSquared = 0, bSquared = 0, ab = 0;
	for (int i = 0; i < N; i++) {
		std::cin >> Va[i];
		if (!std::cin.good()) {
			std::cout << "Nespravny vstup." << std::endl;
			goto cleanup;
		}
	}
	
	for (int i = 0; i < N; i++) {
		std::cin >> Vb[i];
		if (!std::cin.good()) {
			std::cout << "Nespravny vstup." << std::endl;
			goto cleanup;
		}

		aSquared += Va[i] * Va[i];
		bSquared += Vb[i] * Vb[i];
		ab += Va[i] * Vb[i];
	}

	std::cout << "CSM: " << ab / (std::sqrt(aSquared) * std::sqrt(bSquared)) << std::endl;

cleanup:
	delete[] Va;
	delete[] Vb;
	pause();
	return 0;
}