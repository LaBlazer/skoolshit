#include <iostream>

int main() {
	//new a referencia vracia adresu
	const int rows = 10;
	const int cols = 20;

	int pole[rows][cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			pole[i][j] = (j*cols)+i;

	//std::cout << sizeof(int)*N;

	system("pause");
	return 0;
}