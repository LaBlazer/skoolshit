#ifndef __PROGTEST__ 
	#define pause() system("pause"); 
#else
	#define pause(); 
#endif

#include <iostream>

int main() {
	std::cout << "Zadej pocet navstevniku:" << std::endl;
	int visitors, salary;
	double earnings;
	std::cin >> visitors;

	if (std::cin.good() && visitors >= 0) {
		earnings = visitors * 3.5f;
		if (earnings >= 3500) {
			salary = 110;
		}
		else if (earnings >= 3000) {
			salary = 100;
		}
		else if (earnings >= 2500) {
			salary = 90;
		}
		else if (earnings >= 2000) {
			salary = 80;
		}
		else {
			salary = 70;
		}

		std::cout << "Brigadnik vydela: " << salary * 8 << " Kc" << std::endl;
	}
	else {
		std::cout << "Nespravny vstup." << std::endl;
	}
	pause();
	return 0;
}
