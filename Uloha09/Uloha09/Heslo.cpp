#ifndef __PROGTEST__ 
#define pause() system("pause"); 
#else
#define pause(); 
#endif

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

int main() {
	std::string pass;
	std::getline(std::cin, pass);
	bool passed = pass.size() >= 5;
	passed &= std::any_of(pass.begin(), pass.end(), ::isalpha);
	passed &= std::any_of(pass.begin(), pass.end(), ::isdigit);
	passed &= std::any_of(pass.begin(), pass.end(), [](char c) { return !(std::isalnum(c)); });

	std::cout << (passed ? "Heslo splnuje pozadavky." : "Heslo nesplnuje pozadavky.") << std::endl;
	pause();
	return 0;
}