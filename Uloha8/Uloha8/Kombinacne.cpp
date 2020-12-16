#ifndef __PROGTEST__
#define pause() system("pause");
#else
#define pause();
#endif
#include <iostream>

long long factorial(unsigned int i, unsigned int depth) {
	if (i == 1 || depth == 0)
		return 1;
	else
		return i * factorial(i - 1, depth - 1);
}

int main() {
	std::cout << "Zadejte n a k:" << std::endl;
	int n, k, d;
	std::cin >> n >> k;

	if (!std::cin.good() || n < 0 || k < 0 || n < k) {
		std::cout << "Nespravny vstup." << std::endl;
		return 0;
	}

	//n! / (k! * (n - k)!)
	d = n - k;
	std::cout << "C = " << factorial(n, d)/factorial(d, d) << std::endl;
	pause();
	return 0;
}