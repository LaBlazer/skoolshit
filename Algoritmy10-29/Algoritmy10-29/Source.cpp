#include <iostream>

template<typename T>
T** alloc2d(unsigned int &rows, unsigned int &cols) {
	T** arr = new T*[rows];
	for (int i = 0; i < rows; i++)
		arr[i] = new T[cols];

	return arr;
}

template<typename T>
inline void dealloc2d(T** arr, unsigned int &rows) {
	for (int i = 0; i < rows; i++) {
		delete[] arr[i];
	}
	delete[] arr;
	arr = nullptr;
}

int main() {
	unsigned int rows = 5;
	unsigned int cols = 10;
	int** arr = alloc2d<int>(rows, cols);

	for (unsigned int i = 0; i < rows; i++) {
		for(unsigned int j = 0; j < cols; j++) {
			arr[i][j] = (i + 1) * (j + 1);
			std::cout << arr[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	dealloc2d<int>(arr, rows);
	return 0;
}
