#ifndef __PROGTEST__ 
#define pause() system("pause"); 
#else
#define pause(); 
#endif

#include <iostream>
#include <string>

const int N = 5;

struct Patient {
	std::string surname, name, id, disease, insurance;
};

int main() {
	Patient patients[N];

	for (int i = 0; i < N; i++) {
		Patient b;
		std::cout << "Zadejte prijmeni, jmeno, rodne cislo, nemoc a zdravotni pojistovnu pacienta:" << std::endl;
		std::cin >> b.surname >> b.name >> b.id >> b.disease >> b.insurance;
		patients[i] = b;
	}

	
	for (const auto &b : patients) {
		if (b.disease == "tbc") std::cout << "Jmeno a prijmeni pacienta s tbc:" << std::endl << b.name << " " << b.surname << std::endl;
		if (b.insurance == "211") std::cout << "Jmeno a prijmeni pacientu s pojistovnou 211 je:" << std::endl << b.name << " " << b.surname << std::endl;
	}

	std::cout << "Prijmeni vsech pacientu jsou:" << std::endl;
	for (const auto &b : patients)
		std::cout << b.surname << std::endl;

	pause();
	return 0;
}