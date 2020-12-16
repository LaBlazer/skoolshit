#include <iostream>

int main() {
	double d;
	std::cout << "Zadejte cislo:" << std::endl;
	std::cin >> d;
	bool b = std::cin.good() && std::cin.peek() != '.' && std::cin.peek() != 'x' && std::cin.peek() != '-';
	b ? std::cout << d << " : Spravne zadane cislo." : std::cout << "Chybne zadani.";
	std::cout << std::endl;
	return 0;
}