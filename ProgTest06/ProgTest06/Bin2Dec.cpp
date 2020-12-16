#include <iostream>
#include <string>
#include <cmath>

int main() {
	std::string in;
	unsigned int dec = 0;
	std::cout << "Zadej cislo ve dvojkove soustave:" << std::endl;
	std::getline(std::cin, in);
	if (in[0] != '\0') {
		for (int i = 0;; i++) {
			if (in[i] == '0' || in[i] == '1')
				dec = dec * 2 + (in[i] - '0');
			if (in[i] == '\0') {
				std::cout << "Desitkove cislo je: " << dec << std::endl;
				return 0;
			}
		}
	}
	std::cout << "Nespravny vstup." << std::endl;
	return 0;
	
}