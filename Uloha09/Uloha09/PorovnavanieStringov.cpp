#ifndef __PROGTEST__ 
#define pause() system("pause"); 
#else
#define pause(); 
#endif

#include <iostream>
#include <algorithm>
#include <string>

int main() {
	std::cout << "Zadejte 3 slova:" << std::endl;
	std::string s1, s2, s3;
	std::cin >> s1 >> s2 >> s3;
	if (std::cin.good() && std::cin.peek() == '\n') {
		//transform all the strings
		std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
		std::transform(s3.begin(), s3.end(), s3.begin(), ::tolower);
		std::cout << (s1 == s2 ? "Slovo1 a slovo2 jsou stejna." : "Slovo1 a slovo2 nejsou stejna.") << std::endl;
		std::cout << (s1 == s3 ? "Slovo1 a slovo3 jsou stejna." : "Slovo1 a slovo3 nejsou stejna.") << std::endl;
		std::cout << (s2 == s3 ? "Slovo2 a slovo3 jsou stejna." : "Slovo2 a slovo3 nejsou stejna.") << std::endl;
		std::cout << "Pocet znaku ve slovo1 je: " << s1.size() << std::endl;
		std::cout << "Pocet znaku ve slovo2 je: " << s2.size() << std::endl;
		std::cout << "Pocet znaku ve slovo3 je: " << s3.size() << std::endl;
	}
	else {
		std::cout << "Nespravny vstup." << std::endl;
	}
	pause();
	return 0;
}