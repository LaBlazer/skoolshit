#include <iostream>
#include <ctime>
#include <random>

void print_array(bool **mat, unsigned int rows, unsigned int cols) {
	for (unsigned int x = 0; x < rows; x++) {
		for (unsigned int y = 0; y < cols; y++)
			std::cout << (mat[x][y] ? "X" : "O") << "|";
		std::cout << std::endl;
	}
}

void flip(bool **mat, unsigned int rows, unsigned int cols, unsigned int row, unsigned int col) {
	std::cout << "Flipping row: " << row << ", col: " << col << std::endl;
	for (unsigned int x = 0; x < rows; x++) //rows
		mat[x][col] = !mat[x][col];

	for (unsigned int y = 0; y < cols; y++) //cols
		mat[row][y] = !mat[row][y];

	
	mat[row][col] = !mat[row][col];
}

bool is_true(bool **mat, unsigned int rows, unsigned int cols) {
	for (unsigned int x = 0; x < rows; x++)
		for (unsigned int y = 0; y < cols; y++)
			if (!mat[x][y])
				return false;

	return true;
}

int main() {
	const unsigned int rows = 20, cols = 20;

	int iterations;
	std::cout << "Zadajte pocet iteracii: ";
	std::cin >> iterations;

	srand((unsigned int)time(0));

	bool **mat = new bool*[rows];

	for (unsigned int x = 0; x < rows; x++) {
		mat[x] = new bool[cols];
		for (unsigned int y = 0; y < cols; y++)
			mat[x][y] = rand() % 2 == 0;
	}

	print_array(mat, rows, cols);
	system("pause");

	for (; iterations >= 0 && !is_true(mat, rows, cols); iterations--) {
		flip(mat, rows, cols, rand() % rows, rand() % cols);
		print_array(mat, rows, cols);
		system("pause");
	}

	system("pause");
	return 0;
}