#include <iostream>

void lool(int ******a) {
	std::cout << a << std::endl;  //adresa na ktoru odkazuje
	std::cout << &a << std::endl; //adresa pointeru
	std::cout << *a << std::endl; //hodnota na ktoru odkazuje pointer
}

int main() {

	int a = 5;
	int *aa = &a;
	int **aaa = &aa;
	int ***aaaa = &aaa;
	int ****aaaaa = &aaaa;
	int *****aaaaaa = &aaaaa;
	int ******aaaaaaa = &aaaaaa;

	std::cout << ++*&*&*&*&**&**&**&**&**&*&*&*&*aaaaaaa << std::endl;
	
	
	lool(aaaaaaa);
	system("pause");
	return 0;
}