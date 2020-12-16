#include <iostream>

unsigned long long fact(unsigned long long f) {
	if (f == 0)
		return 1;
	for (unsigned long long i = f; i > 1;)
		f *= --i;
	return f;
}

int main()
{
	std::cout << "Zadajte cislo: ";
	int f;
	std::cin >> f;
	if (std::cin.good() && f >= 0 && f <= 20)
		std::cout << "Vysledok: " << fact(f) << std::endl;
	else
		std::cout << "Nespravny vstup!" << std::endl;
	system("pause");
}
