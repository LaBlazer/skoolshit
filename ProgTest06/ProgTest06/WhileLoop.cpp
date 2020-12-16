#include <iostream>

int main() {
	double sum = 0, in;
	std::cout << "Zadavejte cisla, posledni bude 1000:" << std::endl;
	while (std::cin >> in && in != 1000) sum += in;
	sum += 1000;
	std::cout << "Vysledek souctu cisel je: " << sum << std::endl;
	return 0;
}