#include <iostream>
#include <string>

int main() {
	std::cout << "Zadejte pocet schodu:" << std::endl;
	int d = (std::cin >> d, d);
	if(std::cin.fail() || d <= 0) 
		std::cout << "Nespravny vstup." << std::endl; 
	else
		for(int x = 0; x < d; x++) std::cout << std::string(x, 'X') << "_" << std::endl;
	return 0;
}
