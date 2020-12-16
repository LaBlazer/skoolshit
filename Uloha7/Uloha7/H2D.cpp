#ifndef __PROGTEST__ 
#define pause() system("pause"); 
#else
#define pause(); 
#endif
#include <iostream>
#include <sstream>
#include <string>

int main() {
	std::cout << "Zadejte hexadecimalni cislo:" << std::endl;
	std::string hexadecimal;
	std::getline(std::cin, hexadecimal);
	if (hexadecimal.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
		std::cout << "Nespravny vstup." << std::endl;
	else {
		std::istringstream is(hexadecimal);
		unsigned int decimal;
		is >> std::hex >> decimal;
		std::cout << "Desitkove: " << decimal << std::endl;
	}
	pause();
	return 0;
}