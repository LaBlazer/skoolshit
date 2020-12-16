#ifndef __PROGTEST__
#define pause() system("pause");
#else
#define pause();
#endif
#include <iostream>
#include <cmath>

int main() {
	std::cout << "Zadejte interval:" << std::endl;
	int a, b;
	std::cin >> a >> b;

	if (!std::cin.good() || a > b) {
		std::cout << "Nespravny vstup." << std::endl;
		return 0;
	}

	for (; a <= b; a++) {
		if (a < 2) {
			std::cout << 2 << std::endl;
			a = 2;
			continue;
		}
		unsigned int max = std::sqrt(a);
		for (unsigned int i = 2;; i++) {
			if (a % i == 0) break;
			else if (i >= max) {
				std::cout << a << std::endl;
				break;
			}
		}
	}
	pause();
	return 0;
}