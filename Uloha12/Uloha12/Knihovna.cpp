#ifndef __PROGTEST__ 
#define pause() system("pause"); 
#else
#define pause(); 
#endif

#include <iostream>
#include <string>

const int N = 5;

struct Book {
	unsigned int id, release_year, price;
	std::string name, author_name, author_surname, genre;
};

int main() {
	Book library[N];

	for (int i = 0; i < N; i++) {
		Book b;
		std::cout << "Zadej nazev knihy, prijmeni autora, jmeno autora, zanr knihy, rok vydani, cenu a id:" << std::endl;
		std::cin >> b.name >> b.author_surname >> b.author_name >> b.genre >> b.release_year >> b.price >> b.id;
		library[i] = b;
	}

	std::cout << "Romany jsou:" << std::endl;
	for (const auto &b : library)
		if (b.genre == "roman") std::cout << b.name << std::endl;

	std::cout << std::endl << "Knihy s cenou mensi nez 300,- Kc jsou:" << std::endl;
	for (const auto &b : library)
		if (b.price < 300) std::cout << b.name << std::endl;

	std::cout << std::endl << "Prijmeni vsech autoru jsou:" << std::endl;
	for (const auto &b : library)
		std::cout << b.author_surname << std::endl;

	pause();
	return 0;
}