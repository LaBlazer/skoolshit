#ifndef __PROGTEST__ 
#define pause() system("pause"); 
#else
#define pause(); 
#endif
#include <iostream>
#include <string>

int find(int *p, int what, unsigned int stop) {
	for (unsigned int i = 0; i < stop; i++) {
		if (p[i] == what)
			return i;
	}
	return -1;
}

int main() {
	int Na, Nb;
	std::cout << "Zadejte pocet prvku mnoziny A:" << std::endl;
	std::cin >> Na;
	if (!std::cin.good() || Na <= 0) {
		std::cout << "Nespravny vstup." << std::endl;
		pause();
		return 0;
	}
	std::cout << "Zadejte prvky mnoziny A:" << std::endl;
	int *Ma = new int[Na];
	for (int i = 0; i < Na; i++) {
		std::cin >> Ma[i];
		if (!std::cin.good() || find(Ma, Ma[i], i) != -1) {
			std::cout << "Nespravny vstup." << std::endl;
			pause();
			delete[] Ma;
			return 0;
		}
	}

	std::cout << "Zadejte pocet prvku mnoziny B:" << std::endl;
	std::cin >> Nb;
	if (!std::cin.good() || Nb <= 0) {
		std::cout << "Nespravny vstup." << std::endl;
		pause();
		delete[] Ma;
		return 0;
	}
	std::cout << "Zadejte prvky mnoziny B:" << std::endl;
	int *Mb = new int[Nb];
	for (int i = 0; i < Nb; i++) {
		std::cin >> Mb[i];
		if (!std::cin.good() || find(Mb, Mb[i], i) != -1) {
			std::cout << "Nespravny vstup." << std::endl;
			pause();
			delete[] Ma;
			delete[] Mb;
			return 0;
		}
	}
	std::cout << "Prunik mnozin:" << std::endl;

	int *larger, *smaller;
	unsigned int largerSize, smallerSize;
	if (Na > Nb) {
		larger = Ma;
		smaller = Mb;
		largerSize = Na;
		smallerSize = Nb;
	}
	else {
		larger = Ma;
		smaller = Mb;
		largerSize = Na;
		smallerSize = Nb;
	}

	std::string out = "{";
	for (unsigned int i = 0; i < smallerSize; i++) {
		if (find(larger, smaller[i], largerSize) != -1)
			out += std::to_string(smaller[i]) + ", ";
	}
	if (out.size() > 2) {
		out.pop_back();
		out.pop_back();
	}
	out += "}";

	std::cout << out << std::endl;

	delete[] Ma;
	delete[] Mb;

	pause();
	return 0;
}