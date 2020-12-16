#include <iostream>

int main() {

	int a = 232;

	for (int i = sizeof(int)*8; i >= 0; i--)
		std::cout << ((a & (1 << i)) ? "1" : "0");

	std::cout << std::endl;

	system("pause");
	return 0;
}